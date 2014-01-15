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
		HTMLElement element("p");
		element.Content = Text;

		// If not auto position type, add style
		if (PositionType != GUI::PositionType::Auto) {
			std::stringstream style;

			// Add Position Type
			style << "position:";
			if (PositionType == GUI::PositionType::Relative)
				style << "absolute;"; // < This is the CSS equivalent of our Relative
			else
				style << "fixed;"; // < This is the CSS equivalent of our Absolute

			// Add Actual Position
			if (HorizontalAlign == GUI::HorizontalAlign::Left)
				style << "left:";
			else
				style << "right:";
			style << Position.x << ";";

			if (VerticalAlign == GUI::VerticalAlign::Top)
				style << "top:";
			else
				style << "bottom:";
			style << Position.y << ";";

			// And done!
			element.Style = style.str();
		}

		return element;
	}

	/// Dynamic Label ///

	DynamicLabel::DynamicLabel(ViewEventListener &viewListener, std::string htmlId) :
		m_ViewListener(viewListener),
		m_HTMLId(htmlId)
	{}

	void DynamicLabel::SetText(std::string text) {
		if (m_ViewListener.IsReady()) {
			Coherent::UI::View &view = m_ViewListener.GetView();
			view.TriggerEvent("LabelTextChanged", m_HTMLId, text);
		}
	}

	/// Dynamic Label Generator ///

	unsigned int DynamicLabelGenerator::nextId = 0;

	DynamicLabelGenerator::DynamicLabelGenerator(ViewEventListener &viewListener, std::unique_ptr<GUI::IDynamicLabel> &bindingObject) :
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
		std::stringstream idstream;
		idstream << "#label" << ID;
		element.ID = idstream.str();

		return element;
	}
}