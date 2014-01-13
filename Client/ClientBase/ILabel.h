#pragma once

#include "IElement.h"

#include <glm/glm.hpp>

namespace GUI {
	/** Generates a static label, does not give you a binding object. */
	class ILabelGenerator : public IElementGenerator {
	public:
		ILabelGenerator() :
			PositionType(GUI::PositionType::Auto),
			Position(0, 0),
			HorizontalAlign(GUI::HorizontalAlign::Left),
			VerticalAlign(GUI::VerticalAlign::Top)
		{}

	public: // Generation Properties
		// Position Data
		GUI::PositionType PositionType;
		glm::ivec2 Position;
		GUI::HorizontalAlign HorizontalAlign;
		GUI::VerticalAlign VerticalAlign;
	};
}