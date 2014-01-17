#pragma once

#include "Types.h"
#include "IElement.h"

namespace GUI {
	namespace Elements {
		class IView {
		};

		class IViewGenerator : public IElementContainer {
		public: // Generation
			virtual std::unique_ptr<IView> GenerateView() = 0;
		};
	}
}