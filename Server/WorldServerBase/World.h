#pragma once

#include <CommonLib/Events.h>
#include <CommonLib/Logger.h>

#include <memory>

namespace Server {
	namespace Core { class WorldServer; }
	namespace Network { class IWorldDispatcher; }
	namespace Players { struct Player; }

	namespace World {
		class World final {
			Core::WorldServer& m_Server;
			Utils::Logger m_Logger;
			Utils::EventScope m_EventScope;

			std::unique_ptr<Network::IWorldDispatcher> m_Dispatcher;

		public:
			World(Core::WorldServer& server);
			~World();

		public: // Event Callbacks
			void OnPlayerJoined(const Players::Player &player);
		};
	}
}