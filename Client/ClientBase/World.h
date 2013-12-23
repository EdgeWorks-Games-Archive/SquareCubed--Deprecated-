#pragma once

#include "WorldProvider.h"

#include <string>
#include <memory>

namespace Graphics {
	class IGraphics;
	class ITileRenderer;
}

namespace Tools {
	namespace World {
		class World final {
		public: // External Modules
			WorldProvider m_TileProvider;
			std::unique_ptr<Graphics::ITileRenderer> m_TileRenderer;

		public: // Initialization/Uninitialization
			World(Network::INetwork &network, Graphics::IGraphics &graphics, std::string tileArrayPath);
			~World();

		public: // Rendering Functions
			void RenderTiles();
			void RenderObjects();
			void RenderWalls();
		};
	}
}