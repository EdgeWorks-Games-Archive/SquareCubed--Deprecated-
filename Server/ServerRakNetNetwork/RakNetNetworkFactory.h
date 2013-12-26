#pragma once

#include <WorldServerBase/INetworkFactory.h>

namespace Server {
	namespace RakNetNetwork {
		class RakNetNetwork;

		class RakNetNetworkFactory final : public Network::INetworkFactory {
			RakNetNetwork &m_Network;

		public: // Initialization/Uninitialization
			RakNetNetworkFactory(RakNetNetwork &network);

		public: // Packet Handlers
			Network::IPacketHandler* CreatePlayerHandler(Network::IPlayerCallback &callback);

		public: // Packet Dispatchers
			Network::IUnitsDispatcher* CreateUnitsDispatcher();
			Network::IPlayerDispatcher* CreatePlayerDispatcher();
			Network::IWorldDispatcher* CreateWorldDispatcher();
		};
	}
}