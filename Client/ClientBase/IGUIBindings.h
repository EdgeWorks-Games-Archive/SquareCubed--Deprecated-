#pragma once

#include <CommonLib/Events.h>

#include <string>

namespace GUI {
	struct ConnectCallArgs {
		const std::string &Server;
		bool Response;
	};

	class IGUIBindings {
	public: // Initialization/Uninitialization
		virtual ~IGUIBindings() {}

	public: // Calls
		Utils::Event<std::string> OnQuitCall;
		Utils::Event<std::string> OnConnectCall;
		Utils::NoArgsEvent OnRunServerCall;

	public: // Events

	public: // Event Triggers
		virtual void Trigger(const std::string &eventName) = 0;
	};
}