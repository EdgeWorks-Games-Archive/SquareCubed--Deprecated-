#pragma once

#include <list>

namespace DataTypes { struct Chunk; }

namespace Graphics {
	class ITileRenderer {
	public: // Initialization/Uninitialization
		virtual ~ITileRenderer() {}

	public: // Rendering Functions
		virtual void RenderTiles(const std::list<DataTypes::Chunk> &chunks) = 0;
	};
}