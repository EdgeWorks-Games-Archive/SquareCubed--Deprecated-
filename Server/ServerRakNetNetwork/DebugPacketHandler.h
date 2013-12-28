#pragma once

#include "IRakNetPacketHandler.h"

#include <WorldServerBase/Types.h>

namespace Server {
	namespace RakNetNetwork {
		class DebugPacketHandler final : public IRakNetPacketHandler {
			Network::INetwork &m_Network;
			Network::IDebugCallback &m_Callback;

		public: // Initialization/Uninitialization
			DebugPacketHandler(Network::INetwork &network, Network::IDebugCallback &callback);

		public: // Game Loop
			bool HandlePacket(RakNet::Packet &packet);
		};
	}
}