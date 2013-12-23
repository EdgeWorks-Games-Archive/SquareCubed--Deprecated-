#pragma once

#include <WorldServerBase/IWorldDispatcher.h>
#include <WorldServerBase/IClientID.h>

#include <RakPeer.h>

namespace Server {
	namespace RakNetNetwork {
		class RakNetNetwork;

		class WorldDispatcher final : public Network::IWorldDispatcher {
			RakNetNetwork &m_Network;

		public: // Initialization/Uninitialization
			WorldDispatcher(RakNetNetwork &network);

		public: // Send Functions
			void SendWorldChunk(const Network::IClientID& clientId, const DataTypes::Chunk &chunk);
		};
	}
}