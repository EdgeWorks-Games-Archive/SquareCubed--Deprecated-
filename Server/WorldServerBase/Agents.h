#pragma once

#include "IAgent.h"
#include "IClientID.h"

#include <list>
#include <memory>

namespace Server {
	namespace Core { class WorldServer; }
	namespace Network { class IAgentsDispatcher; }

	namespace Agents {
		class Agents final {
			Core::WorldServer &m_Server;
			std::unique_ptr<Network::IAgentsDispatcher> m_Dispatcher;

			std::list<std::unique_ptr<IAgent>> m_Agents;

		public: // Initialization/Uninitialization
			Agents(Core::WorldServer &server);
			~Agents();

		public: // Agent Management Functions
			/** Adds an agent to the class.
			 * Adding an agent means it gets updated and synced.
			 */
			void AddAgent(std::unique_ptr<IAgent> agent);

			/** Removes an agent from the class.
			 * Also deconstructs the agent.
			 */
			void RemoveAgent(unsigned int agentId);

		public: // Networking Functions
			/** Sends all agent descriptors to the client. */
			void SendAllAgentDescs(const Network::IClientID &clientId);

		public: // Game Loop
			/** Updates the class with the given delta. */
			void Update(const float delta);

			/** Sends a wave of packets to all clients.
			 * Will not 'flush' packets, only sends packets
			 * that get sent once every game loop tick.
			 */
			void SendPackets();
		};
	}
}