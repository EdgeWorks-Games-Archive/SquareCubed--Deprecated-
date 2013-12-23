#include "WorldServer.h"

#include "INetwork.h"

#include <CommonLib/ILoggingManager.h>
#include <Physics/AABBBroadphase.h>

#include <thread>
#include <chrono>

namespace Server {
	namespace Core {
		// Initialization/Uninitialization

		WorldServer::WorldServer(Utils::ILoggingManager *loggingManager, Network::INetwork *network) :
			m_Logger(loggingManager->CreateLogger("Server")),

			m_LoggingManager(loggingManager),
			m_Network(network),
			m_Physics(*m_LoggingManager, std::make_unique<Physics::AABBBroadphase>(), 0.01f),
			m_Agents(*this),
			m_Players(*this),
			m_World(*this)
		{
			m_Logger.LogInfo("WSCore::WorldServer Initialized");
		}

		WorldServer::~WorldServer() {
		}

		// Module Accessors

		Utils::ILoggingManager& WorldServer::GetLoggingManager() { return *m_LoggingManager; }
		Network::INetwork& WorldServer::GetNetwork() { return *m_Network; }
		Physics::Physics& WorldServer::GetPhysics() { return m_Physics; }
		Agents::Agents& WorldServer::GetAgents() { return m_Agents; }
		Players::Players& WorldServer::GetPlayers() { return m_Players; }
		World::World& WorldServer::GetWorld() { return m_World; }

		// Game Loop

		void WorldServer::Execute() {
			// Set up Tick Timer Variables
			std::chrono::steady_clock::time_point tickStart;
			std::chrono::duration<float> tickDuration;
			std::chrono::duration<float> tickTargetDuration = std::chrono::duration<float>(0.05f);
			float delta = 0.05f;

			// Run Server Loop
			while (true) {
				// Start Timepoint
				tickStart = std::chrono::steady_clock::now();

				// Handle all Packets
				m_Network->HandlePackets();

				// Update Everything
				m_Agents.Update(delta);

				// Update Physics
				m_Physics.UpdatePhysics(delta);

				// Send all Packets
				m_Agents.SendPackets();

				// Sleep rest of the tick to lock to 50ms per tick
				// Note: weird cast needed because of VC++ bug
				tickDuration = std::chrono::steady_clock::now() - tickStart;
				std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::milliseconds>(tickTargetDuration - tickDuration));

				// Calculate actual delta
				tickDuration = std::chrono::steady_clock::now() - tickStart;
				delta = tickDuration.count();

				// Print Elapsed Time, Uncomment if Needed
				//printf("Elapsed: %fs\n", tickDuration.count());
			}
		}
	}
}