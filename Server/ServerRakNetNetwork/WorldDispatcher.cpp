#include "WorldDispatcher.h"
#include "RakNetNetwork.h"
#include "RakNetClientID.h"

#include <CRakNetNetwork/PacketTypes.h>

#include <BitStream.h>
#include <RakPeer.h>

namespace Server {
	namespace RakNetNetwork {
		WorldDispatcher::WorldDispatcher(RakNetNetwork &network) :
			m_Network(network)
		{
		}

		void WorldDispatcher::SendWorldChunk(const Network::IClientID &clientId, const DataTypes::Chunk &chunk) {
			// Cast to RakNet ID to retrieve GUID
			const RakNetClientID &rakClientId = static_cast<const RakNetClientID&>(clientId);

			// Build Packet to Send
			RakNet::BitStream bs;
			bs.Write(GamePacketIDType::WorldChunk);
			bs.Write(chunk.X);
			bs.Write(chunk.Y);
			for (unsigned int x = 0; x < chunk.CHUNK_MAX_SIZE; x++) {
				for (unsigned int y = 0; y < chunk.CHUNK_MAX_SIZE; y++) {
					bs.Write(chunk.Terrain[x][y]);
				}
			}

			// Send the Packet to the Client
			m_Network.GetRakPeer().Send(&bs, HIGH_PRIORITY, RELIABLE, 0, rakClientId.GUID, false);
		}
	}
}