#pragma once

#include <ClientBase/IState.h>
#include <ClientBase/World.h>
#include <ClientBase/Units.h>
#include <ClientBase/UnitSelect.h>
#include <ClientBase/RPGPlayer.h>

namespace Network {
	class IPacketHandler;
	class IGameDispatcher;
}

namespace Graphics {
	class ITexture2D;
	class ITileArray;
}

namespace GameState {
	class GameState final : public StateEngine::IState {
		Core::Engine &m_Engine;
		std::unique_ptr<Network::IGameDispatcher> m_Dispatcher;

		// Internal Components
		Physics::Physics m_Physics;
		Tools::World::World m_World;
		Tools::Units::Units m_Units;
		Tools::Units::UnitSelect m_UnitSelect;
		Tools::Player::RPGPlayer m_Player;

	public: // Initialization/Uninitialization
		GameState(Core::Engine &engine);
		~GameState();

	public: // Game Loop
		void Update(const float delta);
		void Render(const float delta);
	};
}