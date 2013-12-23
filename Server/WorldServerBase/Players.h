#pragma once

#include "IPlayerCallback.h"
#include "IClientID.h"

#include <CommonLib/Logger.h>
#include <CommonLib/Events.h>

#include <vector>
#include <memory>

namespace Server {
	namespace Core { class WorldServer; }
	namespace Agents { class DynamicAgent; }

	namespace Network {
		class IPacketHandler;
		class IPlayerDispatcher;
	}

	namespace Players {
		struct Player final {
			std::unique_ptr<Network::IClientID> ClientID;
			Agents::DynamicAgent& Agent;

			Player(const Network::IClientID &clientId, Agents::DynamicAgent &agent) :
				ClientID(clientId.Clone()),
				Agent(agent)
			{}
		};

		class Players final : public Network::IPlayerCallback {
			Core::WorldServer& m_Server;
			Utils::Logger m_Logger;

			std::unique_ptr<Network::IPacketHandler> m_PacketHandler;
			std::unique_ptr<Network::IPlayerDispatcher> m_Dispatcher;

			std::vector<std::unique_ptr<Player>> m_Players;

		public:
			Players(Core::WorldServer& server);
			~Players();

		public: // Events
			Utils::Event<Player> OnPlayerJoined;

		public:
			/** Returns a pointer to the player associated with clientId
			 * If no player could be found this function returns nullptr.
			 * \return Pointer to player, nullptr on failure.
			 */
			Player* GetPlayer(const Network::IClientID &clientId);
			void JoinPlayer(const Network::IClientID &clientId);
			void RemovePlayer(const Network::IClientID &clientId);

		public: // Network Callback Functions
			void ReceivedPlayerDisconnected(const Network::IClientID &clientId);
			void ReceivedPlayerPhysicsUpdate(const Network::IClientID &clientId, CNetwork::PhysicsUpdateData physicsData);
		};
	}
}