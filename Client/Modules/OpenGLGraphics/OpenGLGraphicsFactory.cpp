#include "OpenGLGraphicsFactory.h"

#include "TileRenderer.h"
#include "AgentRenderer.h"
#include "SelectionRenderer.h"

#include "Texture2D.h"
#include "TileArray.h"

#include <ClientBase/Content.h>

namespace OpenGLGraphics {
	// Initialization/Uninitialization

	OpenGLGraphicsFactory::OpenGLGraphicsFactory(Content::Content &content) :
		m_Content(content)
	{
	}

	// Renderer Types

	Graphics::ITileRenderer* OpenGLGraphicsFactory::CreateTileRenderer(Graphics::ITileArray &tileArray) {
		return new TileRenderer(tileArray);
	}

	Graphics::IAgentRenderer* OpenGLGraphicsFactory::CreateAgentRenderer(Graphics::ITileArray &tileArray) {
		return new AgentRenderer(tileArray);
	}

	Graphics::ISelectionRenderer* OpenGLGraphicsFactory::CreateSelectionRenderer() {
		return new SelectionRenderer();
	}

	// Content Types

	Graphics::ITexture2D& OpenGLGraphicsFactory::GetTexture2D(const std::string &path) {
		return m_Content.GetContent<Texture2D>(path);
	}

	Graphics::ITileArray& OpenGLGraphicsFactory::GetTileArray(const std::string &path) {
		return m_Content.GetContent<TileArray, Content::Content&>(path, m_Content);
	}
}