#pragma once

#include <ClientBase/IGraphicsFactory.h>

namespace Content { class Content; }

namespace OpenGLGraphics {
	class OpenGLGraphicsFactory final : public Graphics::IGraphicsFactory {
		Content::Content &m_Content;

	public: // Initialization/Uninitialization
		OpenGLGraphicsFactory(Content::Content &content);

	public: // Renderer Types
		Graphics::ITileRenderer* CreateTileRenderer(Graphics::ITileArray &tileArray);
		Graphics::IAgentRenderer* CreateAgentRenderer(Graphics::ITileArray &tileArray);
		Graphics::ISelectionRenderer* CreateSelectionRenderer();

	public: // Content Types
		Graphics::ITexture2D& GetTexture2D(const std::string &path);
		Graphics::ITileArray& GetTileArray(const std::string &path);
	};
}