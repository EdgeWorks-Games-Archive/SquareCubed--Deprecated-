#include "Panel.h"

namespace CoherentUIOpenGLUI {
	/// Panel Generator ///

	void DoNothing() {}

	void PanelGenerator::Generate(std::ostream &output) {
		HTMLElement element = GenerateHTML();
		element.Generate(output);
	}

	// Generation Helpers

	HTMLElement PanelGenerator::GenerateHTML() {
		// Create basic Element
		HTMLElement element = ElementGenerator::GenerateHTML();
		element.Tag = "div";
		element.AddClass("panel");

		// Add all Sub-Elements to Content
		std::stringstream content;
		for (std::unique_ptr<GUI::Elements::IElementGenerator> &element : m_ElementGenerators)
			element->Generate(content);
		element.Content = content.str();

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