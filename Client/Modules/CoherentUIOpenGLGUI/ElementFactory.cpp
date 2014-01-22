#include "ElementFactory.h"

#include "Label.h"
#include "Panel.h"
#include "ProgressBar.h"

namespace CoherentUIOpenGLUI {
	ElementFactory::ElementFactory(ViewEventListener &viewListener) :
		m_ViewListener(viewListener)
	{}

	std::unique_ptr<GUI::Elements::ILabelGenerator> ElementFactory::CreateLabel() {
		return std::make_unique<LabelGenerator>();
	}

	std::unique_ptr<GUI::Elements::IDynamicLabelGenerator> ElementFactory::CreateDynamicLabel(std::unique_ptr<GUI::Elements::IDynamicLabel> &bindingObjPtr) {
		return std::make_unique<DynamicLabelGenerator>(m_ViewListener, bindingObjPtr);
	}

	std::unique_ptr<GUI::Elements::IPanelGenerator> ElementFactory::CreatePanel() {
		return std::make_unique<PanelGenerator>();
	}

	std::unique_ptr<GUI::Elements::IProgressBarGenerator> ElementFactory::CreateProgressBar() {
		return std::make_unique<ProgressBarGenerator>();
	}
}