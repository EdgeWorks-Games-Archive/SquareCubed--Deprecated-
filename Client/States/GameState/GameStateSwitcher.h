#pragma once

namespace StateEngine { class StateEngine; }

namespace GameState {
	void SwitchToState(StateEngine::StateEngine &stateEngine);
	void ImmediateSwitchToState(StateEngine::StateEngine &stateEngine);
}