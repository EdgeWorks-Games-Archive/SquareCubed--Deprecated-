#pragma once

#include <ClientBase/ISelectionRenderer.h>

namespace Graphics { class ITileArray; }

namespace OpenGLGraphics {
	class SelectionRenderer : public Graphics::ISelectionRenderer {
	public: // Initialization/Uninitialization
		SelectionRenderer();

	public: // Rendering Functions
		void RenderUnitSelection(const std::list<std::reference_wrapper<Tools::Units::IUnit>> &units);
		void RenderSelectionBox(const glm::vec2 &bottomLeft, const glm::vec2 &size);
	};
}