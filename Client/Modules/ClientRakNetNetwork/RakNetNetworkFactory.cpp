#include "RakNetNetworkFactory.h"

#include "RakNetNetwork.h"

// Packet Handlers
#include "MainMenuPacketHandler.h"
#include "AgentsPacketHandler.h"
#include "PlayerPacketHandler.h"
#include "WorldPacketHandler.h"

// Packet Dispatchers
#include "GameDispatcher.h"
#include "PlayerDispatcher.h"

namespace RakNetNetwork {
	// Initialization/Uninitialization

	RakNetNetworkFactory::RakNetNetworkFactory(RakNetNetwork &network) :
		m_Network(network)
	{
	}

	// Packet Handlers

	Network::IPacketHandler* RakNetNetworkFactory::CreateMainMenuHandler(Network::IMainMenuCallback &callback) { return new MainMenuPacketHandler(callback); }
	Network::IPacketHandler* RakNetNetworkFactory::CreateAgentsHandler(Network::IAgentsCallback &callback) { return new AgentsPacketHandler(m_Network, callback); }
	Network::IPacketHandler* RakNetNetworkFactory::CreatePlayerHandler(Network::IPlayerCallback &callback) { return new PlayerPacketHandler(m_Network, callback); }
	Network::IPacketHandler* RakNetNetworkFactory::CreateWorldHandler(Network::IWorldCallback &callback) { return new WorldPacketHandler(m_Network, callback); }

	// Packet Dispatchers

	Network::IGameDispatcher* RakNetNetworkFactory::CreateGameDispatcher() { return new GameDispatcher(m_Network); }
	Network::IPlayerDispatcher* RakNetNetworkFactory::CreatePlayerDispatcher() { return new PlayerDispatcher(m_Network); }
}