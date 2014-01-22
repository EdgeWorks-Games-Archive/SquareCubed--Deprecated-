#pragma once

#include "IRakNetPacketHandler.h"

namespace Network {
	class INetwork;
	class IWorldCallback;
}

namespace RakNetNetwork {
	class WorldPacketHandler final : public IRakNetPacketHandler {
		Network::INetwork &m_Network;
		Network::IWorldCallback &m_Callback;

	public: // Initialization/Uninitialization
		WorldPacketHandler(Network::INetwork &network, Network::IWorldCallback &callback);

	public: // Game Loop
		bool HandlePacket(RakNet::Packet &packet);
	};
}