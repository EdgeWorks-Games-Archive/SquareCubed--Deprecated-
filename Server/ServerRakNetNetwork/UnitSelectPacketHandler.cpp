#include "UnitSelectPacketHandler.h"

#include <WorldServerBase/INetwork.h>
#include <WorldServerBase/IUnitSelectCallback.h>

#include <CRakNetNetwork/PacketTypes.h>

#include <BitStream.h>

#include <memory>

namespace Server {
	namespace RakNetNetwork {
		// Initialization/Uninitialization

		UnitSelectPacketHandler::UnitSelectPacketHandler(Network::INetwork &network, Network::IUnitSelectCallback &callback) :
			m_Network(network),
			m_Callback(callback)
		{
		}

		// Game Loop

		bool UnitSelectPacketHandler::HandlePacket(RakNet::Packet &packet) {
			switch (packet.data[0]) {
			
			case (int)GamePacketIDType::UnitOrder: {
				// Set up BitStream
				RakNet::BitStream bs(packet.data, packet.length, false);
				bs.IgnoreBytes(sizeof(RakNet::MessageID));

				// Get the Data
				unsigned int unitId;
				bs.Read(unitId);
				glm::vec2 pos;
				bs.Read(pos.x);
				bool s = bs.Read(pos.y);

				// Make sure the packet is correctly received
				if (!s) {
					//m_Network.ReportProtocolError();
					return true;
				}

				// Call Callback
				m_Callback.ReceivedUnitOrder(unitId, std::move(pos));

				return true;
			}
			}

			return false;
		}
	}
}