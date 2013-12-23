#pragma once

#include <list>
#include <memory>

namespace Tools {
	namespace Agents { class IAgent; }
}

namespace Graphics {
	class ISelectionRenderer {
	public: // Initialization/Uninitialization
		virtual ~ISelectionRenderer() {}

	public: // Rendering Functions
		virtual void RenderSelectionBoxes(const std::list<std::unique_ptr<Tools::Agents::IAgent>> &agents) = 0;
	};
}