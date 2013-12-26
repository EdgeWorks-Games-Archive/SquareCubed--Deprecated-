#include "PlayerPacketHandler.h"

#include <ClientBase/INetwork.h>
#include <ClientBase/IPlayerCallback.h>

#include <CRakNetNetwork/PacketTypes.h>

#include <BitStream.h>

namespace RakNetNetwork {
	// Initialization/Uninitialization

	PlayerPacketHandler::PlayerPacketHandler(Network::INetwork &network, Network::IPlayerCallback &callback) :
		m_Network(network),
		m_Callback(callback)
	{
	}

	// Game Loop

	bool PlayerPacketHandler::HandlePacket(RakNet::Packet &packet) {
		switch (packet.data[0]) {
		case (int) GamePacketIDType::PlayerDesc: {
			// Set up BitStream
			RakNet::BitStream bs(packet.data, packet.length, false);
			bs.IgnoreBytes(sizeof(RakNet::MessageID));

			// Get the Data
			unsigned int unitId;
			bs.Read(unitId);

			DataTypes::Health health;
			bs.Read(health.Current);
			bool s = bs.Read(health.Max);

			// Make sure the packet is correctly received
			if (!s) {
				m_Network.ReportProtocolError();
				return true;
			}

			// Call the Callback Function
			m_Callback.ReceivedPlayerDesc(std::move(unitId), std::move(health));
			} return true;
		}

		return false;
	}
}