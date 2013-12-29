#pragma once

#include "WorldProvider.h"
#include "Types.h"

#include <string>
#include <memory>

namespace Tools {
	namespace World {
		class World final {
		public: // External Modules
			WorldProvider m_TileProvider;
			std::unique_ptr<Graphics::ITileRenderer> m_TileRenderer;

		public: // Initialization/Uninitialization
			World(Core::Engine &engine, std::string tileArrayPath);
			~World();

		public: // Rendering Functions
			void RenderTiles();
			void RenderObjects();
			void RenderWalls();
		};
	}
}