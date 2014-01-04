#include "PlayerPacketHandler.h"
#include "RakNetClientID.h"

#include <WorldServerBase/INetwork.h>
#include <WorldServerBase/IPlayerCallback.h>
#include <WorldServerBase/Players.h>

#include <CRakNetNetwork/PacketTypes.h>

#include <BitStream.h>

namespace Server {
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
			case ID_DISCONNECTION_NOTIFICATION:
			case ID_CONNECTION_LOST: {
				// Get the ID of the disconnected Client
				RakNetNetwork::RakNetClientID clientId(packet.guid);

				// Call Callback
				m_Callback.ReceivedPlayerDisconnected(clientId);

			} return true;
			case (int) GamePacketIDType::PlayerSpawn: {
				// Get the ID of the connected Client
				RakNetNetwork::RakNetClientID clientId(packet.guid);

				// Associate a new Player with the Client that connected
				m_Callback.JoinPlayer(clientId);

			} return true;
			case (int) GamePacketIDType::PlayerPhysicsUpdate: {
				// Get the ID of the Player
				RakNetNetwork::RakNetClientID clientId(packet.guid);

				// Set up BitStream
				RakNet::BitStream bs(packet.data, packet.length, false);
				bs.IgnoreBytes(sizeof(RakNet::MessageID));

				// Get the Data
				CNetwork::PhysicsUpdateData data;
				bs.Read(data.Position.x);
				bs.Read(data.Position.y);
				bs.Read(data.Rotation);
				bs.Read(data.Velocity.x);
				bs.Read(data.Velocity.y);
				bs.Read(data.TargetVelocity.x);
				bool s = bs.Read(data.TargetVelocity.y);

				// Make sure the packet is correctly received
				if (!s) {
					//m_Network.ReportProtocolError();
					return true;
				}

				// Call Callback
				m_Callback.ReceivedPlayerPhysicsUpdate(clientId, std::move(data));

			} return true;
			}

			return false;
		}
	}
}