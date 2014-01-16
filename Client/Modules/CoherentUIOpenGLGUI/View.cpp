#include "View.h"

#include "Label.h"
#include "Panel.h"

#include <fstream>

namespace CoherentUIOpenGLUI {
	/// View ///

	View::View(std::wstring path) :
		m_Path(std::move(path))
	{}

	const std::wstring& View::GetPath() { return m_Path; }

	/// View Generator ///

	ViewGenerator::ViewGenerator(ViewEventListener &viewListener) :
		m_ViewListener(viewListener)
	{}

	// Generation

	std::unique_ptr<GUI::Elements::IView> ViewGenerator::GenerateView() {
		// Generate Output File
		std::ofstream outFile("Content/GUI/_staging/view.html", std::ofstream::out | std::ofstream::trunc);
		Generate(outFile);
		outFile.close();

		// Return View with same Path
		return std::make_unique<View>(L"Content/GUI/_staging/view.html");
	}

	void ViewGenerator::Generate(std::ostream &output) {
		// Start Generating
		output << "<html>\n";

		// Add Head Data
		// TODO: Change this to use a template file
		output << "<head>\n";

		// Add jQuery and jQuery-UI Scripts
		output << "<script src=\"../scripts/jquery-2.0.3.js\"></script>\n";
		output << "<script src=\"../scripts/jquery-ui-1.10.3.js\"></script>\n";

		// Add Coherent UI Scripts
		output << "<script type=\"text/javascript\">engineCreateDeferred = jQuery.Deferred;</script>";
		output << "<script type=\"text/javascript\" src=\"../scripts/coherent.js\"></script>";

		// Add our Custom Bindings Script
		output << "<script type=\"text/javascript\" src=\"../scripts/bindings.js\"></script>\n";

		// Add Style Sheets
		output << "<link rel=\"stylesheet\" href=\"../styling/reset.css\" />\n";
		output << "<link rel=\"stylesheet\" href=\"../styling/style.css\" />\n";

		output << "</head>\n";

		// Add Body
		GenerateBody(output);

		// Finish Generating
		output << "</html>";
	}

	// Internal Generation Helpers

	void ViewGenerator::GenerateBody(std::ostream &output) {
		output << "<body>\n";

		// Add all Sub-Elements to Body
		for (std::unique_ptr<GUI::Elements::IElementGenerator> &element : m_ElementGenerators)
			element->Generate(output);

		output << "</body>\n";
	}

	// Adding Subcomponents

	void ViewGenerator::Add(std::unique_ptr<GUI::Elements::IElementGenerator> element) {
		m_ElementGenerators.push_back(std::move(element));
	}
}