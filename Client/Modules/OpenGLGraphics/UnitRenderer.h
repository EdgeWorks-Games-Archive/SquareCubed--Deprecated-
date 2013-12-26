#pragma once

#include <ClientBase/IUnitRenderer.h>

namespace Graphics { class ITileArray; }

namespace OpenGLGraphics {
	class UnitRenderer : public Graphics::IUnitRenderer {
		Graphics::ITileArray &m_TileTextures;

	public: // Initialization/Uninitialization
		UnitRenderer(Graphics::ITileArray &tileTextures);

	public: // Rendering Functions
		void RenderUnits(const std::list<std::unique_ptr<Tools::Units::IUnit>> &units);
	};
}