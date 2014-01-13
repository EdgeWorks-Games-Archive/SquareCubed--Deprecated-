#include "Label.h"

namespace CoherentUIOpenGLUI {
	LabelGenerator::LabelGenerator(std::string text) :
		m_Text(std::move(text))
	{}

	void LabelGenerator::Generate(std::ostream &output) {
		// If not auto position type, add style attribute
		if (PositionType != GUI::PositionType::Auto) {
			output << "<p style=\"";

			// Add Position Type
			output << "position:";
			if (PositionType == GUI::PositionType::Relative)
				output << "absolute;"; // < This is the CSS equivalent of our Relative
			else
				output << "fixed;"; // < This is the CSS equivalent of our Absolute

			// Add Actual Position
			if (HorizontalAlign == GUI::HorizontalAlign::Left)
				output << "left:";
			else
				output << "right:";
			output << Position.x << ";";

			if (VerticalAlign == GUI::VerticalAlign::Top)
				output << "top:";
			else
				output << "bottom:";
			output << Position.y << ";";

			output << "\">";
		}
		else
			output << "<p>";

		output << m_Text << "</p>\n";
	}
}