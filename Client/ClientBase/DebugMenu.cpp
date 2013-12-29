// Actually, this currently isn't a debug menu, but it will be later.

#ifdef _DEBUG

#include "DebugMenu.h"
#include "Engine.h"
#include "INetwork.h"
#include "INetworkFactory.h"
#include "IDebugDispatcher.h"
#include "Input.h"

namespace Tools {
	namespace Debug {
		DebugMenu::DebugMenu(Core::Engine &engine) :
			m_Dispatcher(engine.GetNetwork().GetFactory().CreateDebugDispatcher()),
			m_Input(engine.GetInput()),
			m_EventScope()
		{
			m_Input.OnKeyChange.AttachMember(this, &DebugMenu::OnKeyChange, m_EventScope);
			Q = m_Input.GetKeyId('Q');
		}

		DebugMenu::~DebugMenu() {}

		void DebugMenu::OnKeyChange(const Input::KeyChangeEventArgs &args) {
			if (args.KeyId == Q && args.Down)
				m_Dispatcher->SpawnUnit(m_Input.GetCursorPosition().World);
		}
	}
}

#endif