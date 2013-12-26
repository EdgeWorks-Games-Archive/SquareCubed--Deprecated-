#pragma once

#include "IRakNetPacketHandler.h"

namespace Network {
	class INetwork;
	class IUnitsCallback;
}

namespace RakNetNetwork {
	class UnitsPacketHandler final : public IRakNetPacketHandler {
		Network::INetwork &m_Network;
		Network::IUnitsCallback &m_Callback;

	public: // Initialization/Uninitialization
		UnitsPacketHandler(Network::INetwork &network, Network::IUnitsCallback &callback);

	public: // Game Loop
		bool HandlePacket(RakNet::Packet &packet);
	};
}