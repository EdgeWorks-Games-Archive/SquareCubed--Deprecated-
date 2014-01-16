#pragma once

#include "IElement.h"

namespace GUI {
	namespace Elements {
		class IPanelGenerator : public IElementGenerator {
		public: // Initialization/Uninitialization
			IPanelGenerator() :
				Size(100, 100)
			{}

		public: // Properties
			glm::uvec2 Size;
		};
	}
}