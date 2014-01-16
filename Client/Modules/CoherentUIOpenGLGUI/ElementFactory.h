#pragma once

#include "Types.h"

#include <ClientBase/IElementFactory.h>

namespace CoherentUIOpenGLUI {
	class ElementFactory final : public GUI::Elements::IElementFactory {
		ViewEventListener &m_ViewListener;

	public:
		ElementFactory(ViewEventListener &viewListener);

		std::unique_ptr<GUI::Elements::ILabelGenerator> CreateLabel();
		std::unique_ptr<GUI::Elements::IDynamicLabelGenerator> CreateDynamicLabel(std::unique_ptr<GUI::Elements::IDynamicLabel> &bindingObjPtr);
		std::unique_ptr<GUI::Elements::IPanelGenerator> CreatePanel();
	};
}