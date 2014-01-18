#include "ProgressBar.h"

namespace CoherentUIOpenGLUI {
	// Generation Helpers

	HTMLElement ProgressBarGenerator::GenerateHTML() {
		// Create basic Element
		HTMLElement element = ElementGenerator::GenerateHTML();
		element.Tag = "progress";

		// Add width style
		element.AddStyle("width", Width);

		return element;
	}
}