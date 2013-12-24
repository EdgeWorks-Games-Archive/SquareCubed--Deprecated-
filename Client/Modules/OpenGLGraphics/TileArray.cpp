#include "TileArray.h"

#include "Texture2D.h"

#include <fstream>

namespace OpenGLGraphics {
	const char* TileArray::GetType() { return "TileArray"; }

	// Initialization/Uninitialization

	TileArray::TileArray(const std::string &path, Content::Content &content) {
		// Read from TileArray Description File
		std::ifstream texArrayDesc(path);
		if (!texArrayDesc.is_open())
			throw std::exception("Failed to open TileArray description file.");

		// Read size from file
		if ((texArrayDesc >> m_MaxId).fail())
			throw std::exception("TileArray description file invalid.");
		m_MaxId--;

		// Initialize Array
		m_Textures = new Graphics::ITexture2D*[m_MaxId + 1];
		for (unsigned int i = 0; i <= m_MaxId; i++) {
			std::string buff;
			texArrayDesc >> buff;
			m_Textures[i] = &content.GetContent<Texture2D>(buff.c_str());
		}
	}

	TileArray::~TileArray() {
		// Delete Array BUT NOT CONTENT
		delete [] m_Textures;
	}

	// Texture Utility Functions

	Graphics::ITexture2D& TileArray::GetTexture(unsigned int index) {
		return *m_Textures[index];
	}
}