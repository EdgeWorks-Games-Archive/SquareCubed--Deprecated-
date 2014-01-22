#pragma once

#include <list>
#include <memory>

namespace Tools {
	namespace Units { class IUnit; }
}

namespace Graphics {
	class IUnitRenderer {
	public: // Initialization/Uninitialization
		virtual ~IUnitRenderer() {}

	public: // Rendering Functions
		virtual void RenderUnits(const std::list<std::unique_ptr<Tools::Units::IUnit>> &units) = 0;
	};
}