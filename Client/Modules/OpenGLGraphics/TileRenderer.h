#pragma once

#include <ClientBase/ITileRenderer.h>

namespace Graphics { class ITileArray; }

namespace OpenGLGraphics {
	class TileRenderer : public Graphics::ITileRenderer {
		Graphics::ITileArray &m_TileTextures;

	public: // Initialization/Uninitialization
		TileRenderer(Graphics::ITileArray &tileTextures);

	public: // Rendering Functions
		void RenderTiles(const std::list<DataTypes::Chunk> &chunks);
	};
}