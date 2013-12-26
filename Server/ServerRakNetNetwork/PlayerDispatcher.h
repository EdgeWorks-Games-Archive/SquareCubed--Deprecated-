#pragma once

#include <WorldServerBase/IPlayerDispatcher.h>
#include <WorldServerBase/IClientID.h>

#include <RakPeer.h>

namespace Server {
	namespace RakNetNetwork {
		class RakNetNetwork;

		class PlayerDispatcher final : public Network::IPlayerDispatcher {
			RakNetNetwork &m_Network;

		public: // Initialization/Uninitialization
			PlayerDispatcher(RakNetNetwork &network);

		public: // Send Functions
			void SendPlayerDesc(const Network::IClientID& clientId, DataTypes::Health health, unsigned int unitId);
		};
	}
}