#include "AgentsDispatcher.h"
#include "RakNetNetwork.h"
#include "RakNetClientID.h"

#include <CRakNetNetwork/PacketTypes.h>

#include <BitStream.h>
#include <RakPeer.h>

namespace Server {
	namespace RakNetNetwork {
		AgentsDispatcher::AgentsDispatcher(RakNetNetwork &network) :
			m_Network(network)
		{
		}

		void AgentsDispatcher::BroadcastAgentPhysics(const unsigned int agentId, const Physics::DynamicRigidBody &rigidBody, const float rotation) {
			// Build Packet to Send
			RakNet::BitStream bs;
			bs.Write(GamePacketIDType::AgentPhysicsUpdate);
			bs.Write(agentId);
			bs.Write(rigidBody.Position.x);
			bs.Write(rigidBody.Position.y);
			bs.Write(rotation);
			bs.Write(rigidBody.Force.x);
			bs.Write(rigidBody.Force.y);
			bs.Write(rigidBody.Velocity.x);
			bs.Write(rigidBody.Velocity.y);

			// Send the Packet to all Clients
			m_Network.GetRakPeer().Send(&bs, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
		}

		void AgentsDispatcher::BroadcastAgentDesc(unsigned int agentId, DataTypes::Health health, unsigned int graphicId) {
			// Call Internal Send Function
			RakSendAgentDesc(RakNet::UNASSIGNED_RAKNET_GUID, true, std::move(agentId), std::move(health), std::move(graphicId));
		}

		void AgentsDispatcher::BroadcastAgentRemove(unsigned int agentId) {
			// Build Packet to Send
			RakNet::BitStream bs;
			bs.Write(GamePacketIDType::AgentRemove);
			bs.Write(agentId);

			// Send the Packet to all Clients
			m_Network.GetRakPeer().Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
		}

		void AgentsDispatcher::SendAgentDesc(const Network::IClientID &clientId, unsigned int agentId, DataTypes::Health health, unsigned int graphicId) {
			// Cast to RakNet ID to retrieve GUID
			const RakNetClientID &rakClientId = static_cast<const RakNetClientID&>(clientId);

			// Call Internal Send Function
			RakSendAgentDesc(rakClientId.GUID, false, std::move(agentId), std::move(health), std::move(graphicId));
		}

		void AgentsDispatcher::RakSendAgentDesc(const RakNet::RakNetGUID &guid, bool broadcast, unsigned int agentId, DataTypes::Health health, unsigned int graphicId) {
			// Build Packet to Send
			RakNet::BitStream bs;
			bs.Write(GamePacketIDType::AgentDesc);
			bs.Write(agentId);
			bs.Write(health.Current);
			bs.Write(health.Max);
			bs.Write(graphicId);

			// Send the Packet to the Client
			m_Network.GetRakPeer().Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, std::move(guid), std::move(broadcast));
		}
	}
}