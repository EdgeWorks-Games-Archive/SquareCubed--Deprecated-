#pragma once

#include <ClientBase/IGUIBindings.h>

namespace CoherentUIOpenGLUI {
	class ViewEventListener;

	class GUIBindings final : public GUI::IGUIBindings {
		ViewEventListener &m_ViewListener;
		Utils::EventScope m_EventScope;

	public: // Initialization/Uninitialization
		GUIBindings(ViewEventListener &viewListener);

	private: // Event Handlers
		void OnViewReadyForBindings(Utils::EmptyEventArgs);

	private: // Internal Binding Wrappers
	};
}