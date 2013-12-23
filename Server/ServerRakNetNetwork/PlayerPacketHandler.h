#pragma once

#include "IRakNetPacketHandler.h"

namespace Server {
	namespace Network {
		class INetwork;
		class IPlayerCallback;
	}

	namespace RakNetNetwork {
		class PlayerPacketHandler final : public IRakNetPacketHandler {
			Network::INetwork &m_Network;
			Network::IPlayerCallback &m_Callback;

		public: // Initialization/Uninitialization
			PlayerPacketHandler(Network::INetwork &network, Network::IPlayerCallback &callback);

		public: // Game Loop
			bool HandlePacket(RakNet::Packet &packet);
		};
	}
}