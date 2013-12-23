#include "StateEngine.h"

namespace StateEngine {
	// Initialization/Uninitialization

	StateEngine::StateEngine(Core::Engine &engine) :
		m_Engine(engine),

		// State Managing Internal
		m_CurrentState(nullptr),
		m_QueuedFactory(),
		m_Loading(false),
		m_Empty(true)
	{
	}

	StateEngine::~StateEngine() {
		// Unload Current State
		if (m_CurrentState != nullptr)
			delete m_CurrentState;
	}

	// State Managing Internal

	void StateEngine::SwitchState(IStateFactory *stateFactory) {
		if (m_Loading)
			throw std::exception("State switch attempt made during existing state switch!");

		// Queue State Switch
		m_Loading = true;
		m_Empty = false;
		m_QueuedFactory = std::unique_ptr<IStateFactory>(stateFactory);
	}

	void StateEngine::ExecuteSwitch() {
		// Unload old State
		if (m_CurrentState != nullptr)
			delete m_CurrentState;

		// Load new State
		m_CurrentState = m_QueuedFactory->New(m_Engine);

		// Clean up and Finish
		m_QueuedFactory.reset();
		m_Loading = false;
	}

	// Game Loop

	void StateEngine::Update(const float delta) {
		if (!m_Loading && !m_Empty)
			m_CurrentState->Update(delta);
		else if (m_QueuedFactory) {
			// Executed Queued state switch
			ExecuteSwitch();
		}
	}

	void StateEngine::Render(const float delta) {
		if (!m_Loading && !m_Empty)
			m_CurrentState->Render(delta);
	}
}