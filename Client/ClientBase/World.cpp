#include "World.h"

#include "IGraphics.h"
#include "IGraphicsFactory.h"
#include "ITileRenderer.h"

namespace Tools {
	namespace World {
		// Initialization/Uninitialization

		World::World(Network::INetwork &network, Graphics::IGraphics &graphics, std::string tileArrayPath) :
			m_TileProvider(network),
			m_TileRenderer(graphics.GetFactory().CreateTileRenderer(
			graphics.GetFactory().GetTileArray(tileArrayPath)
			))
		{
		}

		World::~World() {}

		// Rendering Functions

		void World::RenderTiles() {
			std::list<DataTypes::Chunk> &chunks = m_TileProvider.GetChunks();
			m_TileRenderer->RenderTiles(chunks);
		}

		void World::RenderObjects() {}
		void World::RenderWalls() {}
	}
}