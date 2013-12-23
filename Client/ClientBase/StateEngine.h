#pragma once

#include "IState.h"

#include <memory>

namespace StateEngine {
	class StateEngine final {
		Core::Engine &m_Engine;

	public: // Initialization/Uninitialization
		StateEngine(Core::Engine &engine);
		~StateEngine();

	public: // State Switching
		template<class T> void SwitchState() { SwitchState(new StateFactory<T>()); }
		template<class T> void ImmediateSwitchState() {
			SwitchState(new StateFactory<T>);
			ExecuteSwitch();
		}

	private: // State Managing Internal
		StateEngine::IState *m_CurrentState;
		std::unique_ptr<IStateFactory> m_QueuedFactory;
		bool m_Loading;
		bool m_Empty;

		void SwitchState(IStateFactory *stateFactory);
		void ExecuteSwitch();

	public: // Game Loop
		void Update(const float delta);
		void Render(const float delta);
	};
}