#ifdef _DEBUG

#include "DebugPacketHandler.h"
#include "RakNetClientID.h"

#include <WorldServerBase/INetwork.h>
#include <WorldServerBase/IDebugCallback.h>

#include <CRakNetNetwork/PacketTypes.h>

#include <BitStream.h>

namespace Server {
	namespace RakNetNetwork {
		// Initialization/Uninitialization

		DebugPacketHandler::DebugPacketHandler(Network::INetwork &network, Network::IDebugCallback &callback) :
			m_Network(network),
			m_Callback(callback)
		{
		}

		// Game Loop

		bool DebugPacketHandler::HandlePacket(RakNet::Packet &packet) {
			switch (packet.data[0]) {
			case (int) GamePacketIDType::DebugUnitSpawn: {
				// Set up BitStream
				RakNet::BitStream bs(packet.data, packet.length, false);
				bs.IgnoreBytes(sizeof(RakNet::MessageID));

				// Get the Data
				glm::vec2 data;
				bs.Read(data.x);
				bool s = bs.Read(data.y);

				// Make sure the packet is correctly received
				if (!s) {
					//m_Network.ReportProtocolError();
					return true;
				}

				// Call Callback
				m_Callback.ReceivedSpawnUnit(std::move(data));

				return true;
			}
			}

			return false;
		}
	}
}

#endif