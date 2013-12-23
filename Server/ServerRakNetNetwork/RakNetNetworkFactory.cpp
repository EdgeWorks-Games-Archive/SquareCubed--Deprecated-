#include "RakNetNetworkFactory.h"

#include "RakNetNetwork.h"

// Packet Handlers
#include "PlayerPacketHandler.h"

// Packet Dispatchers
#include "AgentsDispatcher.h"
#include "PlayerDispatcher.h"
#include "WorldDispatcher.h"

namespace Server {
	namespace RakNetNetwork {
		// Initialization/Uninitialization

		RakNetNetworkFactory::RakNetNetworkFactory(RakNetNetwork &network) :
			m_Network(network)
		{
		}

		// Packet Handlers

		Network::IPacketHandler* RakNetNetworkFactory::CreatePlayerHandler(Network::IPlayerCallback &callback) { return new PlayerPacketHandler(m_Network, callback); }

		// Packet Dispatchers

		Network::IAgentsDispatcher* RakNetNetworkFactory::CreateAgentsDispatcher() { return new AgentsDispatcher(m_Network); }
		Network::IPlayerDispatcher* RakNetNetworkFactory::CreatePlayerDispatcher() { return new PlayerDispatcher(m_Network); }
		Network::IWorldDispatcher* RakNetNetworkFactory::CreateWorldDispatcher() { return new WorldDispatcher(m_Network); }
	}
}