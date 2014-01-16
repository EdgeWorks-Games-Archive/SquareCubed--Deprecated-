#pragma once

#include "Types.h"
#include "IElement.h"

#include <memory>

namespace GUI {
	class IView {
	};

	class IViewGenerator {
	public: // Generation
		virtual std::unique_ptr<IView> GenerateView() = 0;

	public: // Adding Subcomponents
		virtual void Add(std::unique_ptr<IElementGenerator> element) = 0;

		// About to be deprecated:
		virtual ILabelGenerator& AddLabel(std::string text) = 0;
		virtual IPanelGenerator& AddPanel() = 0;
	};
}