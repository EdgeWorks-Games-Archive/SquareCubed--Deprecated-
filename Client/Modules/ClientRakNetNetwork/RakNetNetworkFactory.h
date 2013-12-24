#pragma once

#include <ClientBase/INetworkFactory.h>

namespace RakNetNetwork {
	class RakNetNetwork;

	class RakNetNetworkFactory final : public Network::INetworkFactory {
		RakNetNetwork &m_Network;

	public: // Initialization/Uninitialization
		RakNetNetworkFactory(RakNetNetwork &network);

	public: // Packet Handlers
		Network::IPacketHandler* CreateMainMenuHandler(Network::IMainMenuCallback &callback);
		Network::IPacketHandler* CreateAgentsHandler(Network::IAgentsCallback &callback);
		Network::IPacketHandler* CreatePlayerHandler(Network::IPlayerCallback &callback);
		Network::IPacketHandler* CreateWorldHandler(Network::IWorldCallback &callback);

	public: // Packet Dispatchers
		Network::IGameDispatcher* CreateGameDispatcher();
		Network::IPlayerDispatcher* CreatePlayerDispatcher();
	};
}