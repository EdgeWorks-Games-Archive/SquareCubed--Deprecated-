#pragma once

#include "IRakNetPacketHandler.h"

namespace Network {
	class INetwork;
	class IAgentsCallback;
}

namespace RakNetNetwork {
	class AgentsPacketHandler final : public IRakNetPacketHandler {
		Network::INetwork &m_Network;
		Network::IAgentsCallback &m_Callback;

	public: // Initialization/Uninitialization
		AgentsPacketHandler(Network::INetwork &network, Network::IAgentsCallback &callback);

	public: // Game Loop
		bool HandlePacket(RakNet::Packet &packet);
	};
}