#include "WorldProvider.h"

#include "INetwork.h"
#include "INetworkFactory.h"
#include "IPacketHandler.h"

namespace Tools {
	namespace World {
		WorldProvider::WorldProvider(Network::INetwork &network) :
			m_Network(network),
			m_PacketHandler(m_Network.GetFactory().CreateWorldHandler(*this)),
			m_LoadedChunks()
		{
			m_Network.Attach(*m_PacketHandler);
		}

		WorldProvider::~WorldProvider() {
			m_Network.Detach(*m_PacketHandler);
		}

		std::list<DataTypes::Chunk>& WorldProvider::GetChunks() {
			return m_LoadedChunks;
		}

		void WorldProvider::TestSetTile(int cx, int cy, int x, int y, unsigned int id) {
			for (DataTypes::Chunk &chunk : m_LoadedChunks) {
				if (chunk.X == cx && chunk.Y == cy) {
					chunk.Terrain[x][y] = id;
					return;
				}
			}
		}

		// Callback Functions

		void WorldProvider::ReceivedWorldChunk(DataTypes::Chunk chunk) {
			m_LoadedChunks.push_back(std::move(chunk));
		}
	}
}