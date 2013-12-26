#include "GUIBindings.h"

#include "ViewEventListener.h"

#include <Coherent/UI/Binding/String.h>

#include <thread>

namespace CoherentUIOpenGLUI {
	// Initialization/Uninitialization

	GUIBindings::GUIBindings(ViewEventListener &viewListener) :
		m_ViewListener(viewListener)
	{
		m_ViewListener.OnViewReadyForBindings.AttachFromThis(GUIBindings::OnViewReadyForBindings, m_EventScope);
	}

	// Event Handlers

	void GUIBindings::OnViewReadyForBindings(Utils::EmptyEventArgs) {
		Coherent::UI::View &view = m_ViewListener.GetView();
		view.BindCall("Quit", Coherent::UI::MakeHandler(&OnQuitCall, &Utils::Event<std::string>::Invoke));
		view.BindCall("Connect", Coherent::UI::MakeHandler(&OnConnectCall, &Utils::Event<std::string>::Invoke));
		view.BindCall("RunServer", Coherent::UI::MakeHandler(&OnRunServerCall, &Utils::NoArgsEvent::Invoke));
	}

	// Internal Binding Wrappers

	// Event Triggers

	void GUIBindings::Trigger(const std::string &eventName) {
		Coherent::UI::View &view = m_ViewListener.GetView();
		view.TriggerEvent(eventName.c_str());
	}
}