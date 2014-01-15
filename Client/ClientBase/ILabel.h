#pragma once

#include "IElement.h"

#include <glm/glm.hpp>

#include <string>

namespace GUI {
	/// Static Label ///

	/** Generates a static label, does not give you a binding object. */
	class ILabelGenerator : public IElementGenerator {
	public:
		ILabelGenerator() :
			Text(),
			PositionType(GUI::PositionType::Auto),
			Position(0, 0),
			HorizontalAlign(GUI::HorizontalAlign::Left),
			VerticalAlign(GUI::VerticalAlign::Top)
		{}
		virtual ~ILabelGenerator() {}

	public: // Properties
		std::string Text;

		// Position Data
		GUI::PositionType PositionType;
		glm::ivec2 Position;
		GUI::HorizontalAlign HorizontalAlign;
		GUI::VerticalAlign VerticalAlign;
	};

	/// Dynamic Label ///

	class IDynamicLabel {
	public:
		virtual ~IDynamicLabel() {}
		virtual void SetText(std::string text) = 0;
	};

	class IDynamicLabelGenerator : public virtual ILabelGenerator {
	public:
		virtual ~IDynamicLabelGenerator() {}
	};
}