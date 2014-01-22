#include "World.h"

#include "Engine.h"
#include "IGraphics.h"
#include "IGraphicsFactory.h"
#include "ITileRenderer.h"

namespace Tools {
	namespace World {
		// Initialization/Uninitialization

		World::World(Core::Engine &engine, std::string tileArrayPath) :
			m_TileProvider(engine.GetNetwork()),
			m_TileRenderer(engine.GetGraphics().GetFactory().CreateTileRenderer(
				engine.GetGraphics().GetFactory().GetTileArray(tileArrayPath)
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