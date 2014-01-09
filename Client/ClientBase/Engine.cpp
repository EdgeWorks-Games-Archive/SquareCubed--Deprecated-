#include "Engine.h"

#include "Content.h"
#include "IContext.h"
#include "IGraphics.h"
#include "IWindow.h"
#include "Input.h"
#include "INetwork.h"
#include "IGUI.h"
#include "IGUIBindings.h"
#include "StateEngine.h"

#include <CommonLib/ILoggingManager.h>

#include <thread>
#include <chrono>

namespace Core {
	// Initialization/Uninitialization

	Engine::Engine(Utils::ILoggingManager *loggingManager) :
		m_Logger(loggingManager->CreateLogger("Engine")),
		m_Running(false),
		m_LoggingManager(loggingManager)
	{
		m_Logger.LogInfo("Core::Engine Initialized");
	}

	Engine::~Engine() {
	}

	// Module Setters

	void Engine::SetContent(Content::Content *content) {
		if (m_Context)
			throw std::exception("Content Module Already Assigned");
		m_Content = std::unique_ptr<Content::Content>(content);
	}

	void Engine::SetContext(Context::IContext *context) {
		if (m_Context)
			throw std::exception("Context Module Already Assigned");
		m_Context = std::unique_ptr<Context::IContext>(context);
	}

	void Engine::SetGraphics(Graphics::IGraphics *graphics) {
		if (m_Graphics)
			throw std::exception("Graphics Module Already Assigned");
		m_Graphics = std::unique_ptr<Graphics::IGraphics>(graphics);
	}

	void Engine::SetInput(Input::Input *input) {
		if (m_Input)
			throw std::exception("Input Module Already Assigned");
		m_Input = std::unique_ptr<Input::Input>(input);
	}

	void Engine::SetNetwork(Network::INetwork *network) {
		if (m_Network)
			throw std::exception("Network Module Already Assigned");
		m_Network = std::unique_ptr<Network::INetwork>(network);
	}

	void Engine::SetGUI(GUI::IGUI *gui) {
		if (m_GUI)
			throw std::exception("GUI Module Already Assigned");
		m_GUI = std::unique_ptr<GUI::IGUI>(gui);
	}

	void Engine::SetStateEngine(StateEngine::StateEngine *stateEngine) {
		if (m_StateEngine)
			throw std::exception("State Engine Module Already Assigned");
		m_StateEngine = std::unique_ptr<StateEngine::StateEngine>(stateEngine);
	}

	// Module Accessors

	Utils::ILoggingManager& Engine::GetLoggingManager() { return *m_LoggingManager; }
	Content::Content& Engine::GetContent() { return *m_Content; }
	Context::IContext& Engine::GetContext() { return *m_Context; }
	Graphics::IGraphics& Engine::GetGraphics() { return *m_Graphics; }
	Input::Input& Engine::GetInput() { return *m_Input; }
	Network::INetwork& Engine::GetNetwork() { return *m_Network; }
	GUI::IGUI& Engine::GetGUI() { return *m_GUI; }
	StateEngine::StateEngine& Engine::GetStateEngine() { return *m_StateEngine; }

	// Game Loop

	void Engine::Execute() {
		// Set up Tick Timer Variables
		std::chrono::steady_clock::time_point tickStart;
		std::chrono::duration<float> tickDuration;
		//std::chrono::duration<float> tickTargetDuration = std::chrono::duration<float>(0.016f);
		float delta = 0.016f;

		// Hook Core Events
		m_GUI->GetBindings().OnQuitCall.AttachMember(this, &Engine::OnQuitCall, m_EventScope);

		// Run Game Loop
		m_Running = true;
		while (m_Running) {
			if (m_Context->GetMainWindow().HasCloseRequest())
				m_Running = false;

			// Start Timepoint
			tickStart = std::chrono::steady_clock::now();

			// Handle all Packets
			m_Network->HandlePackets();

			// Poll Window Events
			m_Context->PollEvents();

			// Update Everything
			m_StateEngine->Update(delta);
			m_GUI->Update();
			
			// Update input afterwards since camera position
			// might change during other update functions.
			m_Input->Update();
			
			// Render the State Engine
			m_Graphics->BeginRender();
			m_StateEngine->Render(delta);

			// Render the GUI
			m_Graphics->BeginGUIRender();
			m_GUI->Render();

			// Finish Rendering
			m_Graphics->EndRender();

			// TODO: Make sure this gets activated if vsync is off
			// Sleep rest of the tick to lock to 16ms per tick
			// Note: weird cast needed because of VC++ bug
			//tickDuration = std::chrono::steady_clock::now() - tickStart;
			//std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::milliseconds>(tickTargetDuration - tickDuration));

			// Calculate actual delta
			tickDuration = std::chrono::steady_clock::now() - tickStart;
			delta = tickDuration.count();

			// Print Elapsed Time, Uncomment if Needed
			// printf("Elapsed: %fs\n", tickDuration.count());
		}
	}

	void Engine::OnQuitCall(const std::string &str) {
		m_Logger.LogInfo("Shutting down Engine: %s", str.c_str());
		m_Running = false;
	}
}