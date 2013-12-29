// Actually, this currently isn't a debug menu, but it will be later.

#include "DebugMenu.h"
#include "Engine.h"
#include "INetwork.h"
#include "INetworkFactory.h"
#include "IDebugDispatcher.h"
#include "Input.h"

namespace Tools {
	namespace Debug {
		DebugMenu::DebugMenu(Core::Engine &engine, Input::Input &input) :
			m_Dispatcher(engine.GetNetwork().GetFactory().CreateDebugDispatcher()),
			m_Input(input),
			m_EventScope()
		{
			engine.GetInput().OnKeyChange.AttachMember(this, &DebugMenu::OnKeyChange, m_EventScope);
			Q = input.GetKeyId('Q');
		}

		DebugMenu::~DebugMenu() {}

		void DebugMenu::OnKeyChange(const Input::KeyChangeEventArgs &args) {
			if (args.KeyId == Q)
				m_Dispatcher->SpawnUnit(m_Input.GetCursorPosition().Absolute);
		}
	}
}