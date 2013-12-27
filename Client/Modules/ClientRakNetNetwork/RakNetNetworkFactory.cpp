#include "RakNetNetworkFactory.h"

#include "RakNetNetwork.h"

// Packet Handlers
#include "MainMenuPacketHandler.h"
#include "UnitsPacketHandler.h"
#include "PlayerPacketHandler.h"
#include "WorldPacketHandler.h"

// Packet Dispatchers
#include "GameDispatcher.h"
#include "PlayerDispatcher.h"
#include "DebugDispatcher.h"

namespace RakNetNetwork {
	// Initialization/Uninitialization

	RakNetNetworkFactory::RakNetNetworkFactory(RakNetNetwork &network) :
		m_Network(network)
	{
	}

	// Packet Handlers

	Network::IPacketHandler* RakNetNetworkFactory::CreateMainMenuHandler(Network::IMainMenuCallback &callback) { return new MainMenuPacketHandler(callback); }
	Network::IPacketHandler* RakNetNetworkFactory::CreateUnitsHandler(Network::IUnitsCallback &callback) { return new UnitsPacketHandler(m_Network, callback); }
	Network::IPacketHandler* RakNetNetworkFactory::CreatePlayerHandler(Network::IPlayerCallback &callback) { return new PlayerPacketHandler(m_Network, callback); }
	Network::IPacketHandler* RakNetNetworkFactory::CreateWorldHandler(Network::IWorldCallback &callback) { return new WorldPacketHandler(m_Network, callback); }

	// Packet Dispatchers

	Network::IGameDispatcher* RakNetNetworkFactory::CreateGameDispatcher() { return new GameDispatcher(m_Network); }
	Network::IPlayerDispatcher* RakNetNetworkFactory::CreatePlayerDispatcher() { return new PlayerDispatcher(m_Network); }
#ifdef _DEBUG
	std::unique_ptr<Network::IDebugDispatcher> RakNetNetworkFactory::CreateDebugDispatcher() { return std::make_unique<DebugDispatcher>(m_Network); }
#endif
}