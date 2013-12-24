#include "MainMenuState.h"
#include "MainMenuStateSwitcher.h"

#include <ClientBase/Engine.h>
#include <ClientBase/Content.h>
#include <ClientBase/IGUI.h>
#include <ClientBase/IGUIBindings.h>
#include <ClientBase/StateEngine.h>
#include <ClientBase/INetwork.h>
#include <ClientBase/INetworkFactory.h>
#include <ClientBase/IPacketHandler.h>
#include <States/GameState/GameStateSwitcher.h>

#include <thread>

namespace MainMenuState {
	// Factory to avoid including the big compiler-grinding-to-a-crawl file
	void SwitchToState(StateEngine::StateEngine &stateEngine) { stateEngine.SwitchState<MainMenuState>(); }
	void ImmediateSwitchToState(StateEngine::StateEngine &stateEngine) { stateEngine.ImmediateSwitchState<MainMenuState>(); }

	// Initialization/Uninitialization

	MainMenuState::MainMenuState(Core::Engine &engine) :
		m_Engine(engine),
		m_PacketHandler(m_Engine.GetNetwork().GetFactory().CreateMainMenuHandler(*this)),
		m_EventScope()
	{
		m_Engine.GetNetwork().Attach(*m_PacketHandler);

		// Bind UI Callbacks
		m_Engine.GetGUI().GetBindings().OnConnectCall.AttachMember(this, &MainMenuState::OnConnectCall, m_EventScope);
		m_Engine.GetGUI().GetBindings().OnRunServerCall.AttachMember(this, &MainMenuState::OnRunServerCall, m_EventScope);

		// Done Loading, Switch UI
		m_Engine.GetGUI().SwitchView(L"MainMenu");
	}

	MainMenuState::~MainMenuState() {
		// Detach Packet Handlers
		m_Engine.GetNetwork().Detach(*m_PacketHandler);

		// Free all Content
		m_Engine.GetContent().ClearContent();
	}

	// Network Callback Functions

	void MainMenuState::ReceivedRequestAccepted() {
		GameState::SwitchToState(m_Engine.GetStateEngine());
	}

	// Game Loop

	void MainMenuState::Update(const float delta) {
	}

	void MainMenuState::Render(const float delta) {
	}

	// Event Callbacks

	void MainMenuState::OnConnectCall(const std::string &server) {
		m_Engine.GetNetwork().Connect(server.c_str(), 6789);
	}

#if defined _DEBUG && _WIN32
	void MainMenuState::OnRunServerCall(const Utils::EmptyEventArgs &args) {
		system("start Bin\\WorldServer.exe");
	}
#else
	void MainMenuState::OnRunServerCall(const Utils::EmptyEventArgs &args) {}
#endif
}