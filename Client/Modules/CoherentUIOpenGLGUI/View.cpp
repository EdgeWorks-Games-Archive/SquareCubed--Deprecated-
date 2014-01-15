#include "View.h"

#include "Label.h"

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

	std::unique_ptr<GUI::IView> ViewGenerator::GenerateView() {
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
		for (std::unique_ptr<GUI::IElementGenerator> &element : m_ElementGenerators)
			element->Generate(output);

		output << "</body>\n";
	}

	// Adding Subcomponents

	GUI::ILabelGenerator& ViewGenerator::AddLabel(std::string text) {
		// Create the Object and Set Values
		GUI::ILabelGenerator &label = AddNew<LabelGenerator>();
		label.Text = std::move(text);

		// Return the Reference
		return label;
	}

	GUI::IDynamicLabelGenerator& ViewGenerator::AddDynamicLabel(std::unique_ptr<GUI::IDynamicLabel> &bindingObject, std::string text) {
		// Create the Object and Set Values
		GUI::IDynamicLabelGenerator &label = AddNew<DynamicLabelGenerator>(m_ViewListener, bindingObject);
		label.Text = std::move(text);

		// Return the Reference
		return label;
	}

	// Subcomponent Helpers

	template<class T>
	T& ViewGenerator::AddNew() {
		// Create the Object
		std::unique_ptr<T> obj = std::make_unique<T>();

		// Keep a Reference to it and Move it to the List
		T &objRef = *obj;
		m_ElementGenerators.push_back(std::move(obj));

		// Return the Reference
		return objRef;
	}

	template<class T, class BindingT>
	T& ViewGenerator::AddNew(ViewEventListener &viewListener, std::unique_ptr<BindingT> &bindingObject) {
		// Create the Object
		std::unique_ptr<T> obj = std::make_unique<T>(viewListener, bindingObject);

		// Keep a Reference to it and Move it to the List
		T &objRef = *obj;
		m_ElementGenerators.push_back(std::move(obj));

		// Return the Reference
		return objRef;
	}
}