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
		HTMLElement element;
		element.Tag = "p";
		element.Content = Text;

		// If not auto position type, add style
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