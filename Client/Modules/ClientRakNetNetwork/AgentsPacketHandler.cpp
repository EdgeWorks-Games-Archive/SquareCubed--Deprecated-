#include "AgentsPacketHandler.h"

#include <ClientBase/INetwork.h>
#include <ClientBase/IAgentsCallback.h>

#include <CommonLib/PacketTypes.h>
#include <CommonLib/PhysicsPacketDataTypes.h>

#include <BitStream.h>

namespace RakNetNetwork {
	// Initialization/Uninitialization

	AgentsPacketHandler::AgentsPacketHandler(Network::INetwork &network, Network::IAgentsCallback &callback) :
		m_Network(network),
		m_Callback(callback)
	{
	}

	// Game Loop

	bool AgentsPacketHandler::HandlePacket(RakNet::Packet &packet) {
		switch (packet.data[0]) {
		case (int) GamePacketIDType::AgentPhysicsUpdate: {
			// Set up BitStream
			RakNet::BitStream bs(packet.data, packet.length, false);
			bs.IgnoreBytes(sizeof(RakNet::MessageID));

			// Get the Data
			unsigned int agentId;
			bs.Read(agentId);

			CNetwork::PhysicsUpdateData data;
			bs.Read(data.Position.x);
			bs.Read(data.Position.y);
			bs.Read(data.Rotation);
			bs.Read(data.Force.x);
			bs.Read(data.Force.y);
			bs.Read(data.Velocity.x);
			bool s = bs.Read(data.Velocity.y);

			// Make sure the packet is correctly received
			if (!s) {
				m_Network.ReportProtocolError();
				return true;
			}

			// Call the Callback Function
			m_Callback.ReceivedUpdateAgentPhysics(agentId, data);
			} return true;
		case (int) GamePacketIDType::AgentDesc: {
			// Set up BitStream
			RakNet::BitStream bs(packet.data, packet.length, false);
			bs.IgnoreBytes(sizeof(RakNet::MessageID));

			// Get the Data
			unsigned int agentId;
			bs.Read(agentId);

			DataTypes::Health health;
			bs.Read(health.Current);
			bs.Read(health.Max);

			unsigned int graphicId;
			bool s = bs.Read(graphicId);

			// Make sure the packet is correctly received
			if (!s) {
				m_Network.ReportProtocolError();
				return true;
			}

			// Call the Callback Function
			m_Callback.ReceivedAgentDesc(std::move(agentId), std::move(health), std::move(graphicId));
			} return true;
		case (int) GamePacketIDType::AgentRemove: {
			// Set up BitStream
			RakNet::BitStream bs(packet.data, packet.length, false);
			bs.IgnoreBytes(sizeof(RakNet::MessageID));

			// Get the Data
			unsigned int agentId;
			bool s = bs.Read(agentId);

			// Make sure the packet is correctly received
			if (!s) {
				m_Network.ReportProtocolError();
				return true;
			}

			// Call the Callback Function
			m_Callback.ReceivedRemoveAgent(agentId);
			} return true;
		}

		return false;
	}
}