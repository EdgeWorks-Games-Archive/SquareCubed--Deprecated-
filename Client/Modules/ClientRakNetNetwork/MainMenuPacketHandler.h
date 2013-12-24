#pragma once

#include "IRakNetPacketHandler.h"

namespace Network { class IMainMenuCallback; }

namespace RakNetNetwork {
	class MainMenuPacketHandler final : public IRakNetPacketHandler {
		Network::IMainMenuCallback &m_Callback;

	public: // Initialization/Uninitialization
		MainMenuPacketHandler(Network::IMainMenuCallback &callback);

	public: // Game Loop
		bool HandlePacket(RakNet::Packet &packet);
	};
}