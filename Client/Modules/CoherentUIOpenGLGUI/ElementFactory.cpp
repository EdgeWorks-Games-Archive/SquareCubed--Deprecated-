#include "ElementFactory.h"

#include "Label.h"

namespace CoherentUIOpenGLUI {
	ElementFactory::ElementFactory(ViewEventListener &viewListener) :
		m_ViewListener(viewListener)
	{}

	std::unique_ptr<GUI::IDynamicLabelGenerator> ElementFactory::CreateDynamicLabel(std::unique_ptr<GUI::IDynamicLabel> &bindingObjPtr) {
		return std::make_unique<DynamicLabelGenerator>(m_ViewListener, bindingObjPtr);
	}
}