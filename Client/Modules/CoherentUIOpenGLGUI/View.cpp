#include "View.h"

#include "Label.h"

namespace CoherentUIOpenGLUI {
	/// View ///

	View::View(std::wstring path) :
		m_Path(std::move(path))
	{}

	const std::wstring& View::GetPath() { return m_Path; }

	/// View Generator ///

	// Generation

	std::unique_ptr<GUI::IView> ViewGenerator::GenerateView() {
		// Generate Output File
		std::ofstream outFile("Content/GUI/_staging/view.html", std::ofstream::out | std::ofstream::trunc);
		Generate(outFile);
		outFile.close();

		// Return View with same Path
		return std::make_unique<View>(L"Content/GUI/_staging/view.html");
	}

	void ViewGenerator::Generate(std::ofstream &file) {
		file << "<html><body>\n";

		// Add all Sub-Elements
		for (std::unique_ptr<GUI::IElementGenerator> &element : m_ElementGenerators)
			element->Generate(file);

		file << "</body></html>";
	}

	// Adding Subcomponents

	GUI::ILabelGenerator& ViewGenerator::AddLabel(std::string text) {
		// Create a new Label
		std::unique_ptr<GUI::ILabelGenerator> label = std::make_unique<LabelGenerator>(std::move(text));

		// Keep a reference to the old Label and add it to the list
		GUI::ILabelGenerator &retLabel = *label;
		m_ElementGenerators.push_back(std::move(label));
		
		// Return the reference
		return retLabel;
	}
}