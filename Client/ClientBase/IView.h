#pragma once

#include "Types.h"
#include "IElement.h"

#include <memory>

namespace GUI {
	class IView : public IElement {
	};

	class IViewGenerator : public IElementGenerator {
	public: // Generation
		virtual std::unique_ptr<IView> GenerateView() = 0;

	public: // Adding Subcomponents
		virtual ILabelGenerator& AddLabel(std::string text) = 0;
	};
}