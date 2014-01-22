#include "ProgressBar.h"

namespace CoherentUIOpenGLUI {
	// Generation Helpers

	HTMLElement ProgressBarGenerator::GenerateHTML() {
		// Create Container Element
		HTMLElement element = ElementGenerator::GenerateHTML();
		element.Tag = "div";
		element.AddClass("progress-container");

		std::stringstream content;

		// Add Label if Needed
		if (Label != "") {
			element.AddStyle("width", Width + LabelWidth);

			// Create Label
			HTMLElement label;
			label.Tag = "p";
			label.AddStyle("width", LabelWidth);
			HTMLHelper::Escape(Label);
			label.Content = Label;

			// Add Label to Content
			label.Generate(content);
		}
		else
			element.AddStyle("width", Width);

		// Create Progress Bar
		HTMLElement bar;
		bar.Tag = "progress";
		bar.AddStyle("width", Width);

		// Add Value and Max
		if (Max != 0) {
			bar.AddAttribute("value", Value);
			bar.AddAttribute("max", Max);
		}

		// Add Color if Needed
		if (Color != GUI::Elements::ColorType::None) {
			switch (Color) {
			case GUI::Elements::ColorType::Red:		bar.AddClass("red"); break;
			case GUI::Elements::ColorType::Blue:	bar.AddClass("blue"); break;
			case GUI::Elements::ColorType::Yellow:	bar.AddClass("yellow"); break;
			}
		}

		// Finish off Generating
		bar.Generate(content);
		element.Content = content.str();

		return element;
	}
}