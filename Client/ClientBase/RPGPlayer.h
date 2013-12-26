#pragma once

#include "IPlayerCallback.h"
#include "PlayerUnit.h"

#include <CommonLib/Logger.h>

#include <memory>

namespace Core { class Engine; }

namespace Network {
	class INetwork;
	class IPacketHandler;
	class IPlayerDispatcher;
}

namespace Input { class Input; }

namespace Graphics {
	class IGraphics;
	class ICamera;
}

namespace Tools {
	namespace Units { class Units; }

	namespace Player {
		class RPGPlayer final : public Network::IPlayerCallback {
			// Logger
			Utils::Logger m_Logger;

			// External Components
			Network::INetwork &m_Network;
			Input::Input &m_Input;
			Tools::Units::Units &m_Units;
			Physics::Physics &m_Physics;

			// Internal Components
			Tools::Units::PlayerUnit *m_Unit;
			std::unique_ptr<Network::IPacketHandler> m_PacketHandler;
			std::unique_ptr<Network::IPlayerDispatcher> m_Dispatcher;

		private: // Physics Change Check Properties
			glm::vec2 m_PreviousForce;

		private: // Player Properties
			float m_Speed;
			float m_Deadzone;

		private: // Camera Properties
			Graphics::ICamera &m_Camera;
			glm::vec3 &m_CameraPosition;
			glm::vec2 &m_CameraSize;

		public: // Initialization/Uninitialization
			/** Initializes a new instance of RPGPlayer.
			 * The player will not be added to the world until the
			 * server responds with a player descriptor packet.
			 * \param[in,out]	engine	Reference to the engine base object.
			 * \param[in,out]	units	Reference to the units tool.
			 * \param[in,out]	physics	Reference to the physics engine.
			 */
			RPGPlayer(Core::Engine &engine, Tools::Units::Units &units, Physics::Physics &physics);
			~RPGPlayer();

		public: // Network Callback Functions
			/** Called by network.
			 * Do not call this manually.
			 */
			void ReceivedPlayerDesc(unsigned int unitId, DataTypes::Health health);

		public: // Game Loop
			/** Updates the state of the player.
			 * \param	delta	The delta time in seconds.
			 */
			void Update(float delta);
		};
	}
}