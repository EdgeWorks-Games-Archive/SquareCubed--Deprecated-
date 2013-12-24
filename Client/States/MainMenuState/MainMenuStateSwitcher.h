#pragma once

namespace StateEngine { class StateEngine; }

namespace MainMenuState {
	void SwitchToState(StateEngine::StateEngine &stateEngine);
	void ImmediateSwitchToState(StateEngine::StateEngine &stateEngine);
}