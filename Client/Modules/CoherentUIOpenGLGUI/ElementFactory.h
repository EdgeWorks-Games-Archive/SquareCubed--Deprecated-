#pragma once

#include "Types.h"

#include <ClientBase/IElementFactory.h>

namespace CoherentUIOpenGLUI {
	class ElementFactory final : public GUI::IElementFactory {
		ViewEventListener &m_ViewListener;

	public:
		ElementFactory(ViewEventListener &viewListener);

		std::unique_ptr<GUI::ILabelGenerator> CreateLabel();
		std::unique_ptr<GUI::IDynamicLabelGenerator> CreateDynamicLabel(std::unique_ptr<GUI::IDynamicLabel> &bindingObjPtr);
		std::unique_ptr<GUI::IPanelGenerator> CreatePanel();
	};
}