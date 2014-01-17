#include "Element.h"

namespace CoherentUIOpenGLUI {
	// Internal Generation Helpers

	HTMLElement ElementGenerator::GenerateHTML() {
		HTMLElement element;

		// If not auto position type, set style
		if (PositionType != GUI::Elements::PositionType::Auto) {
			// Add Position Type
			if (PositionType == GUI::Elements::PositionType::Relative)
				element.AddStyle("position", "absolute"); // < This is the CSS equivalent of our Relative
			else
				element.AddStyle("position", "fixed"); // < This is the CSS equivalent of our Absolute

			// Add Actual Position
			if (HorizontalPos == GUI::Elements::HorizontalAlign::Left)
				element.AddStyle("left", Position.x);
			else
				element.AddStyle("right", Position.x);

			if (VerticalPos == GUI::Elements::VerticalAlign::Top)
				element.AddStyle("top", Position.y);
			else
				element.AddStyle("bottom", Position.y);
		}

		return element;
	}
}