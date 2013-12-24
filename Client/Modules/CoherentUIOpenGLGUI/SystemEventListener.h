#pragma once

#include "ViewEventListener.h"

#include "CoherentUI.h"

namespace CoherentUIOpenGLUI {
	class CoherentUIOpenGLUI;

	class SystemEventListener final : public Coherent::UI::EventListener {
		ViewEventListener &m_ViewListener;
		Coherent::UI::UISystem *m_System;

	public: // Initialization/Uninitialization
		SystemEventListener(ViewEventListener &viewListener);

	public: // Utility Functions
		virtual void SystemReady() COHERENT_OVERRIDE;
		void SetSystem(Coherent::UI::UISystem* system);
	};
}