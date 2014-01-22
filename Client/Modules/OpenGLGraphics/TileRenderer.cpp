#include "TileRenderer.h"

#include <ClientBase/ITileArray.h>
#include <ClientBase/ITexture2D.h>

#include <CommonLib/worldtypes.h>

#include "GLheaders.h"

namespace OpenGLGraphics {
	// Initialization/Uninitialization

	TileRenderer::TileRenderer(Graphics::ITileArray &tileTextures) :
		m_TileTextures(tileTextures)
	{}

	// Rendering Functions
	void TileRenderer::RenderTiles(const std::list<DataTypes::Chunk> &chunks) {
		for (const DataTypes::Chunk& chunk : chunks) {
			glPushMatrix();
			glTranslated(chunk.X * DataTypes::Chunk::CHUNK_MAX_SIZE, chunk.Y * DataTypes::Chunk::CHUNK_MAX_SIZE, 0);
			for (unsigned int x = 0; x < DataTypes::Chunk::CHUNK_MAX_SIZE; x++) {
				for (unsigned int y = 0; y < DataTypes::Chunk::CHUNK_MAX_SIZE; y++) {
					m_TileTextures.GetTexture(chunk.Terrain[x][y]).Render(0, 0, 1, 1);
					glTranslated(0, 1, 0);
				}
				glTranslated(1, -DataTypes::Chunk::CHUNK_MAX_SIZE, 0);
			}
			glPopMatrix();
		}
	}
}