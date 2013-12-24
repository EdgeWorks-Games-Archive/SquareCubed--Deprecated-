#include <ClientBase/Engine.h>
#include <ClientBase/IContext.h>
#include <ClientBase/StateEngine.h>
#include <ClientBase/Input.h>
#include <ClientBase/Content.h>

#include <Modules/GLFWContext/GLFWContextLoader.h>
#include <Modules/OpenGLGraphics/OpenGLGraphicsLoader.h>
#include <Modules/ClientRakNetNetwork/RakNetNetworkLoader.h>
#include <Modules/CoherentUIOpenGLGUI/CoherentUIOpenGLUILoader.h>

#include <States/MainMenuState/MainMenuStateSwitcher.h>

#include <CommonLib/LoggingManager.h>

int main(int argc, char* args []) {
	// Initialize Logger
	Utils::ILoggingManager *loggingManager = new Utils::LoggingManager("./Logs/Client.log");
	Utils::Logger logger = loggingManager->CreateLogger("Loader");

	logger.LogHighlight("Initializing all Engine Modules...");

	// Initialize Engine
	Core::Engine engine(loggingManager);
	
	// Set up Content Module
	Content::Content *content = new Content::Content(*loggingManager);
	engine.SetContent(content);

	// Set up Context Module
	Context::IContext *context = GLFWContext::LoadContext();
	engine.SetContext(context);

	// Set up Graphics Module
	Graphics::IGraphics *graphics = OpenGLGraphics::LoadGraphics(context->GetMainWindow(), *content);
	engine.SetGraphics(graphics);

	// Set up Input Module
	Input::Input *input = new Input::Input(*context);
	engine.SetInput(input);

	// Set up Network Module
	Network::INetwork *network = RakNetNetwork::LoadNetwork(*loggingManager);
	engine.SetNetwork(network);

	// Set up GUI Module
	GUI::IGUI *gui = CoherentUIOpenGLUI::LoadGUI(*loggingManager, *input);
	engine.SetGUI(gui);

	// Set up State Engine
	StateEngine::StateEngine *stateEngine = new StateEngine::StateEngine(engine);
	engine.SetStateEngine(stateEngine);

	logger.LogHighlight("All Engine Modules Initialized");
	logger.LogHighlight("Queueing Default State Initialization...");

	// Set Default State
	MainMenuState::SwitchToState(*stateEngine);

	logger.LogHighlight("Executing Main Loop...");

	// Run Engine
	engine.Execute();
}