#pragma once

#include "Units.h"
#include "Players.h"
#include "World.h"
#include "Debug.h"

#include <CommonLib/Logger.h>
#include <Physics/Physics.h>

#include <memory>

namespace Server {
	namespace Network { class INetwork; }

	namespace Core {
		class WorldServer final {
			Utils::Logger m_Logger;
			bool m_KeepRunning;

		public: // Initialization/Uninitialization
			WorldServer(Utils::ILoggingManager *loggingManager, Network::INetwork *network);
			~WorldServer();

		private: // Modules
			std::unique_ptr<Utils::ILoggingManager> m_LoggingManager;
			std::unique_ptr<Network::INetwork> m_Network;
			Physics::Physics m_Physics;
			Units::Units m_Units;
			Players::Players m_Players;
			World::World m_World;
#ifdef _DEBUG
			Debug::Debug m_Debug;
#endif

		public: // Module Accessors
			/// <summary>Gets the Logging Manager</summary>
			/// <returns>The Logging Manager</returns>
			Utils::ILoggingManager& GetLoggingManager();

			/// <summary>Gets the Network Module</summary>
			/// <returns>The Network Module</returns>
			Network::INetwork& GetNetwork();

			/// <summary>Gets the Physics Module</summary>
			/// <returns>The Physics Module</returns>
			Physics::Physics& GetPhysics();

			/// <summary>Gets the Units Module</summary>
			/// <returns>The Units Module</returns>
			Units::Units& GetUnits();

			/// <summary>Gets the Players Module</summary>
			/// <returns>The Units Module</returns>
			Players::Players& GetPlayers();

			/// <summary>Gets the World Module</summary>
			/// <returns>The World Module</returns>
			World::World& GetWorld();

		public: // Game Loop
			/// <summary>Executes this Instance</summary>
			void Execute();
		};
	}
}