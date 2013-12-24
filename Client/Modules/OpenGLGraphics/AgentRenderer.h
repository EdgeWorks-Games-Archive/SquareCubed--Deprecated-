#pragma once

#include <ClientBase/IAgentRenderer.h>

namespace Graphics { class ITileArray; }

namespace OpenGLGraphics {
	class AgentRenderer : public Graphics::IAgentRenderer {
		Graphics::ITileArray &m_TileTextures;

	public: // Initialization/Uninitialization
		AgentRenderer(Graphics::ITileArray &tileTextures);

	public: // Rendering Functions
		void RenderAgents(const std::list<std::unique_ptr<Tools::Agents::IAgent>> &agents);
	};
}