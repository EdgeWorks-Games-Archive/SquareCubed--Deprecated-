#pragma once

#include "IRakNetPacketHandler.h"

#include <WorldServerBase/Types.h>

namespace Server {
	namespace RakNetNetwork {
		class UnitSelectPacketHandler final : public IRakNetPacketHandler {
			Network::INetwork &m_Network;
			Network::IUnitSelectCallback &m_Callback;

		public: // Initialization/Uninitialization
			UnitSelectPacketHandler(Network::INetwork &network, Network::IUnitSelectCallback &callback);

		public: // Game Loop
			bool HandlePacket(RakNet::Packet &packet);
		};
	}
}