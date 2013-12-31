#pragma once

#include <glm/glm.hpp>

#include <list>
#include <memory>

namespace Tools {
	namespace Units { class IUnit; }
}

namespace Graphics {
	class ISelectionRenderer {
	public: // Initialization/Uninitialization
		virtual ~ISelectionRenderer() {}

	public: // Rendering Functions
		virtual void RenderUnitSelection(const std::list<std::reference_wrapper<Tools::Units::IUnit>> &units) = 0;
		virtual void RenderSelectionBox(const glm::vec2 &bottomLeft, const glm::vec2 &size) = 0;
	};
}