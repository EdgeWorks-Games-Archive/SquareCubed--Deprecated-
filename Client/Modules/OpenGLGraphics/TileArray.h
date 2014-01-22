#pragma once

#include <ClientBase/ITileArray.h>
#include <ClientBase/IContentBase.h>

#include <ClientBase/Content.h>

#include <string>

namespace OpenGLGraphics {
	class TileArray final : public Graphics::ITileArray, public Content::IContentBase {
	public: static const char* GetType();

	public: // Initialization/Uninitialization
		TileArray(const std::string &path, Content::Content &content);
		~TileArray();

	private: // Properties
		unsigned int m_MaxId;
		Graphics::ITexture2D** m_Textures;

	public: // Texture Utility Functions
		Graphics::ITexture2D& GetTexture(unsigned int index);
	};
}