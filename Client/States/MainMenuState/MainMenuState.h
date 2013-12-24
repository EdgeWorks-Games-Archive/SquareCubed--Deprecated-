#pragma once

#include <ClientBase/IState.h>
#include <ClientBase/IMainMenuCallback.h>

#include <CommonLib/Events.h>

#include <memory>
#include <string>

namespace Network { class IPacketHandler; }

namespace MainMenuState {
	class MainMenuState final : public StateEngine::IState, public Network::IMainMenuCallback {
		Core::Engine &m_Engine;
		std::unique_ptr<Network::IPacketHandler> m_PacketHandler;
		Utils::EventScope m_EventScope;
		
	public: // Initialization/Uninitialization
		MainMenuState(Core::Engine &engine);
		~MainMenuState();

	public: // Network Callback Functions
		void ReceivedRequestAccepted();

	public: // Game Loop
		void Update(const float delta);
		void Render(const float delta);

	private: // Event Callbacks
		void OnConnectCall(const std::string &server);
		void OnRunServerCall(const Utils::EmptyEventArgs &args);
	};
}