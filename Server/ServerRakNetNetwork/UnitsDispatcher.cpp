#include "UnitsDispatcher.h"
#include "RakNetNetwork.h"
#include "RakNetClientID.h"

#include <CRakNetNetwork/PacketTypes.h>

#include <BitStream.h>
#include <RakPeer.h>

namespace Server {
	namespace RakNetNetwork {
		UnitsDispatcher::UnitsDispatcher(RakNetNetwork &network) :
			m_Network(network)
		{
		}

		void UnitsDispatcher::BroadcastUnitPhysics(const unsigned int unitId, const Physics::DynamicRigidBody &rigidBody, const float rotation) {
			// Build Packet to Send
			RakNet::BitStream bs;
			bs.Write(GamePacketIDType::UnitPhysicsUpdate);
			bs.Write(unitId);
			bs.Write(rigidBody.Position.x);
			bs.Write(rigidBody.Position.y);
			bs.Write(rotation);
			bs.Write(rigidBody.Velocity.x);
			bs.Write(rigidBody.Velocity.y);
			bs.Write(rigidBody.TargetVelocity.x);
			bs.Write(rigidBody.TargetVelocity.y);

			// Send the Packet to all Clients
			m_Network.GetRakPeer().Send(&bs, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
		}

		void UnitsDispatcher::BroadcastUnitDesc(unsigned int unitId, DataTypes::Health health, unsigned int graphicId) {
			// Call Internal Send Function
			RakSendUnitDesc(RakNet::UNASSIGNED_RAKNET_GUID, true, std::move(unitId), std::move(health), std::move(graphicId));
		}

		void UnitsDispatcher::BroadcastUnitRemove(unsigned int unitId) {
			// Build Packet to Send
			RakNet::BitStream bs;
			bs.Write(GamePacketIDType::UnitRemove);
			bs.Write(unitId);

			// Send the Packet to all Clients
			m_Network.GetRakPeer().Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
		}

		void UnitsDispatcher::SendUnitDesc(const Network::IClientID &clientId, unsigned int unitId, DataTypes::Health health, unsigned int graphicId) {
			// Cast to RakNet ID to retrieve GUID
			const RakNetClientID &rakClientId = static_cast<const RakNetClientID&>(clientId);

			// Call Internal Send Function
			RakSendUnitDesc(rakClientId.GUID, false, std::move(unitId), std::move(health), std::move(graphicId));
		}

		void UnitsDispatcher::RakSendUnitDesc(const RakNet::RakNetGUID &guid, bool broadcast, unsigned int unitId, DataTypes::Health health, unsigned int graphicId) {
			// Build Packet to Send
			RakNet::BitStream bs;
			bs.Write(GamePacketIDType::UnitDesc);
			bs.Write(unitId);
			bs.Write(health.Current);
			bs.Write(health.Max);
			bs.Write(graphicId);

			// Send the Packet to the Client
			m_Network.GetRakPeer().Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, std::move(guid), std::move(broadcast));
		}
	}
}