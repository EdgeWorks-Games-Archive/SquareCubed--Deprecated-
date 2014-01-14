#pragma once

#include <ClientBase/Types.h>
#include <ClientBase/IState.h>
#include <ClientBase/World.h>
#include <ClientBase/Units.h>
#include <ClientBase/UnitSelect.h>
#include <ClientBase/RPGPlayer.h>
#include <ClientBase/FPSTimer.h>
#include <ClientBase/DebugMenu.h>

namespace GameState {
	class GameState final : public StateEngine::IState {
		Core::Engine &m_Engine;
		std::unique_ptr<Network::IGameDispatcher> m_Dispatcher;
		std::unique_ptr<GUI::IViewGenerator> m_ViewGenerator;
		std::unique_ptr<GUI::IView> m_View;

		// Internal Components
		Physics::Physics m_Physics;
		Tools::World::World m_World;

		Tools::Units::Units m_Units;
		Tools::Units::UnitSelect m_UnitSelect;
		Tools::Player::RPGPlayer m_Player;

#ifdef _DEBUG
		Tools::Misc::FPSTimer m_FPSTimer;
		Tools::Debug::DebugMenu m_DebugMenu;
#endif

	public: // Initialization/Uninitialization
		GameState(Core::Engine &engine);
		~GameState();

	public: // Game Loop
		void Update(const float delta);
		void Render(const float delta);
	};
}