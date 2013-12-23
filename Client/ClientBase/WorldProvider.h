#pragma once

#include <ClientBase/IWorldCallback.h>

#include <CommonLib/worldtypes.h>

#include <memory>
#include <list>

namespace Network {
	class IPacketHandler;
	class INetwork;
}

namespace Tools {
	namespace World {
		class WorldProvider final : public Network::IWorldCallback {
			Network::INetwork &m_Network;
			std::unique_ptr<Network::IPacketHandler> m_PacketHandler;
			std::list<DataTypes::Chunk> m_LoadedChunks;

		public:
			WorldProvider(Network::INetwork &network);
			~WorldProvider();

			std::list<DataTypes::Chunk>& GetChunks();
			void TestSetTile(int cx, int cy, int x, int y, unsigned int id);

		public: // Callback Functions
			void ReceivedWorldChunk(DataTypes::Chunk chunk);
		};
	}
}