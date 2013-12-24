#include "SystemEventListener.h"

#include "CoherentUIOpenGLUI.h"

namespace CoherentUIOpenGLUI {
	// Initialization/Uninitialization

	SystemEventListener::SystemEventListener(ViewEventListener &viewListener) :
		m_ViewListener(viewListener),
		m_System(nullptr)
	{}

	// Utility Functions

	void SystemEventListener::SystemReady() {
		// Perhaps inform something? Doesn't seem to be needed right now.
	}

	void SystemEventListener::SetSystem(Coherent::UI::UISystem* system) {
		m_System = system;
	}
}