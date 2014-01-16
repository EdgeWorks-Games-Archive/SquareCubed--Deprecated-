#include "ElementFactory.h"

#include "Label.h"
#include "Panel.h"

namespace CoherentUIOpenGLUI {
	ElementFactory::ElementFactory(ViewEventListener &viewListener) :
		m_ViewListener(viewListener)
	{}

	std::unique_ptr<GUI::ILabelGenerator> ElementFactory::CreateLabel() {
		return std::make_unique<LabelGenerator>();
	}

	std::unique_ptr<GUI::IDynamicLabelGenerator> ElementFactory::CreateDynamicLabel(std::unique_ptr<GUI::IDynamicLabel> &bindingObjPtr) {
		return std::make_unique<DynamicLabelGenerator>(m_ViewListener, bindingObjPtr);
	}

	std::unique_ptr<GUI::IPanelGenerator> ElementFactory::CreatePanel() {
		return std::make_unique<PanelGenerator>();
	}
}