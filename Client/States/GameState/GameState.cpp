#include "GameState.h"
#include "GameStateSwitcher.h"

#include <ClientBase/Engine.h>
#include <ClientBase/Content.h>
#include <ClientBase/IGraphics.h>
#include <ClientBase/IGraphicsFactory.h>
#include <ClientBase/ICamera.h>
#include <ClientBase/IGUI.h>
#include <ClientBase/StateEngine.h>
#include <ClientBase/INetwork.h>
#include <ClientBase/INetworkFactory.h>
#include <ClientBase/IGameDispatcher.h>

#include <CommonLib/LoggingManager.h>
#include <Physics/AABBBroadphase.h>

#include <string>

namespace GameState {
	// Factory to avoid including the big compiler-grinding-to-a-crawl file
	void SwitchToState(StateEngine::StateEngine &stateEngine) { stateEngine.SwitchState<GameState>(); }
	void ImmediateSwitchToState(StateEngine::StateEngine &stateEngine) { stateEngine.ImmediateSwitchState<GameState>(); }

	GameState::GameState(Core::Engine &engine) :
		m_Engine(std::move(engine)),
		m_Dispatcher(m_Engine.GetNetwork().GetFactory().CreateGameDispatcher()),
		
		// Internal Components
		m_Physics(m_Engine.GetLoggingManager(), std::make_unique<Physics::AABBBroadphase>(), 0.01f),
		m_World(
			m_Engine.GetNetwork(),
			m_Engine.GetGraphics(),
			"../Content/Tiles/tiles.scta"
		),
		m_Agents(
			m_Engine.GetNetwork(),
			m_Engine.GetGraphics(),
			m_Physics,
			"../Content/Agents/agents.scta"
		),
		m_Player(m_Engine, m_Agents, m_Physics)
	{
		// Set Camera Size
		m_Engine.GetGraphics().GetMainCamera().SetHeight(14);

		// Done Loading, Switch UI and Spawn the Player
		m_Engine.GetGUI().SwitchView(L"Game");
		m_Dispatcher->SpawnPlayer();
	}

	GameState::~GameState() {
		// Disconnect
		m_Engine.GetNetwork().Disconnect();

		// Free all Content
		m_Engine.GetContent().ClearContent();
	}

	void GameState::Update(const float delta) {
		m_Player.Update(delta);
		m_Physics.UpdatePhysics(delta);
	}

	void GameState::Render(const float delta) {
		// Render Tiles
		m_World.RenderTiles();

		// Render Objects
		m_World.RenderObjects();

		// Render Agents
		m_Agents.RenderAgents();

		// Render Walls
		m_World.RenderWalls();
	}
}