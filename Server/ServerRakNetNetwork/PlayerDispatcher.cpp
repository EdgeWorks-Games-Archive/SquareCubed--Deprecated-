#include "PlayerDispatcher.h"
#include <BitStream.h>
#include <RakPeer.h>
#include "RakNetNetwork.h"
#include "RakNetClientID.h"

#include <CRakNetNetwork/PacketTypes.h>

namespace Server {
	namespace RakNetNetwork {
		PlayerDispatcher::PlayerDispatcher(RakNetNetwork &network) :
			m_Network(network)
		{
		}

		void PlayerDispatcher::SendPlayerDesc(const Network::IClientID &clientId, DataTypes::Health health, unsigned int agentId) {
			// Cast to RakNet ID to retrieve GUID
			const RakNetClientID &rakClientId = static_cast<const RakNetClientID&>(clientId);

			// Build Packet to Send
			RakNet::BitStream bs;
			bs.Write(GamePacketIDType::PlayerDesc);
			bs.Write(agentId);
			bs.Write(health.Current);
			bs.Write(health.Max);

			// Send the Packet to the Client
			m_Network.GetRakPeer().Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, rakClientId.GUID, false);
		}
	}
}