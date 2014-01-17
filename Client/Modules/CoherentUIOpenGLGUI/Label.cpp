#include "Label.h"

#include "ViewEventListener.h"

#include <Coherent/UI/Binding/String.h>

#include <sstream>

namespace CoherentUIOpenGLUI {
	/// Static Label Generator ///

	LabelGenerator::~LabelGenerator() {}

	void LabelGenerator::Generate(std::ostream &output) {
		HTMLElement element = GenerateHTML();
		element.Generate(output);
	}

	// Generation Helpers

	HTMLElement LabelGenerator::GenerateHTML() {
		// Create basic Element
		HTMLElement element = ElementGenerator::GenerateHTML();
		element.Tag = "p";
		element.Content = Text;

		// If italic, set style
		if (Italic) element.AddStyle("font-style", "italic");

		return element;
	}

	/// Dynamic Label ///

	DynamicLabel::DynamicLabel(ViewEventListener &viewListener, std::string htmlId) :
		m_ViewListener(viewListener),
		m_HTMLId("#" + std::move(htmlId))
	{}

	void DynamicLabel::SetText(std::string text) {
		if (m_ViewListener.IsReady()) {
			Coherent::UI::View &view = m_ViewListener.GetView();
			view.TriggerEvent("LabelTextChanged", m_HTMLId, text);
		}
	}

	/// Dynamic Label Generator ///

	unsigned int DynamicLabelGenerator::nextId = 0;

	DynamicLabelGenerator::DynamicLabelGenerator(ViewEventListener &viewListener, std::unique_ptr<GUI::Elements::IDynamicLabel> &bindingObject) :
		m_ViewListener(viewListener),
		ID(nextId),
		BindingObject(bindingObject)
	{
		nextId++;
	}

	void DynamicLabelGenerator::Generate(std::ostream &output) {
		HTMLElement element = GenerateHTML();
		element.Generate(output);
		BindingObject = std::make_unique<DynamicLabel>(m_ViewListener, element.ID);
	}

	// Generation Helpers

	HTMLElement DynamicLabelGenerator::GenerateHTML() {
		HTMLElement element = LabelGenerator::GenerateHTML();

		// Add ID
		std::stringstream idStream;
		idStream << "label" << ID;
		element.ID = idStream.str();

		return element;
	}
}