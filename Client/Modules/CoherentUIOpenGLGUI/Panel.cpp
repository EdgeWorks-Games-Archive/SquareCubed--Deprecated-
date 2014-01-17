#include "Panel.h"

namespace CoherentUIOpenGLUI {
	/// Panel Generator ///

	void PanelGenerator::Generate(std::ostream &output) {
		HTMLElement element = GenerateHTML();
		element.Generate(output);
	}

	// Generation Helpers

	HTMLElement PanelGenerator::GenerateHTML() {
		// Create basic Element
		HTMLElement element;
		element.Tag = "div";
		element.AddClass("panel");

		// Add all Sub-Elements to Content
		std::stringstream content;
		for (std::unique_ptr<GUI::Elements::IElementGenerator> &element : m_ElementGenerators)
			element->Generate(content);
		element.Content = content.str();

		// If not auto position type, Add position style
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

		// Add size style
		element.AddStyle("width", Size.x);
		element.AddStyle("height", Size.y);

		return element;
	}

	// Adding Subcomponents

	void PanelGenerator::Add(std::unique_ptr<GUI::Elements::IElementGenerator> element) {
		m_ElementGenerators.push_back(std::move(element));
	}
}