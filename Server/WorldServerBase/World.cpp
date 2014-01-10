#include "World.h"

#include "WorldServer.h"
#include "INetwork.h"
#include "INetworkFactory.h"
#include "IWorldDispatcher.h"

#include <CommonLib/LoggingManager.h>

namespace Server {
	namespace World {
		World::World(Core::WorldServer& server) :
			m_Server(server),
			m_Logger(m_Server.GetLoggingManager().CreateLogger("World")),
			m_EventScope(),

			m_Dispatcher(server.GetNetwork().GetFactory().CreateWorldDispatcher())
		{
			// Hook Events
			m_Server.GetPlayers().OnPlayerJoined.AttachMember(this, &World::OnPlayerJoined, m_EventScope);
		}

		World::~World() {}

		// Event Callbacks

		void World::OnPlayerJoined(const Players::Player &player) {
			// Send Dummy Data
			DataTypes::Chunk testChunk(-1, 0);
			m_Dispatcher->SendWorldChunk(*player.ClientID, testChunk);
			testChunk.Y = -1;
			m_Dispatcher->SendWorldChunk(*player.ClientID, testChunk);
			testChunk.X = 0;
			m_Dispatcher->SendWorldChunk(*player.ClientID, testChunk);

			// More complex test chunk
			testChunk.Y = 0;
			testChunk.Terrain[1][1] = 1;
			testChunk.Terrain[2][1] = 1;
			testChunk.Terrain[1][2] = 1;
			testChunk.Terrain[2][2] = 1;
			m_Dispatcher->SendWorldChunk(*player.ClientID, testChunk);

			m_Logger.LogInfo("World Data sent to new Player");
		}
	}
}