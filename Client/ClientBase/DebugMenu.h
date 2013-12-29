#pragma once

#include "Types.h"

#include <CommonLib/Events.h>

#include <memory>

namespace Tools {
	namespace Debug {
		class DebugMenu final {
			std::unique_ptr<Network::IDebugDispatcher> m_Dispatcher;
			Utils::EventScope m_EventScope;
			Input::Input &m_Input;
			Input::KeyID Q;

			void OnKeyChange(const Input::KeyChangeEventArgs &args);
		public:
			DebugMenu(Core::Engine &engine, Input::Input &input);
			~DebugMenu();
			
		};
	}
}