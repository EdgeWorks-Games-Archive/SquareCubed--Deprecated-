#include "RakNetNetworkFactory.h"

#include "RakNetNetwork.h"

// Packet Handlers
#include "PlayerPacketHandler.h"
#include "DebugPacketHandler.h"

// Packet Dispatchers
#include "UnitsDispatcher.h"
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
#ifdef _DEBUG
		std::unique_ptr<Network::IPacketHandler> RakNetNetworkFactory::CreateDebugHandler(Network::IDebugCallback &callback) { return std::make_unique<DebugPacketHandler>(m_Network, callback); }
#endif

		// Packet Dispatchers

		Network::IUnitsDispatcher* RakNetNetworkFactory::CreateUnitsDispatcher() { return new UnitsDispatcher(m_Network); }
		Network::IPlayerDispatcher* RakNetNetworkFactory::CreatePlayerDispatcher() { return new PlayerDispatcher(m_Network); }
		Network::IWorldDispatcher* RakNetNetworkFactory::CreateWorldDispatcher() { return new WorldDispatcher(m_Network); }
	}
}