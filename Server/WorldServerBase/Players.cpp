#include "Players.h"
#include "Units.h"
#include "BaseUnitTypes.h"
#include "INetwork.h"
#include "INetworkFactory.h"
#include "IPacketHandler.h"
#include "IPlayerDispatcher.h"
#include "IPlayerCallback.h"

#include <CommonLib/ILoggingManager.h>

#include "WorldServer.h"

namespace Server {
	namespace Players {
		Players::Players(Core::WorldServer& server) :
			m_Server(server),
			m_Logger(server.GetLoggingManager().CreateLogger("Players")),

			m_PacketHandler(server.GetNetwork().GetFactory().CreatePlayerHandler(*this)),
			m_Dispatcher(server.GetNetwork().GetFactory().CreatePlayerDispatcher()),

			m_Players()
		{
			/* Reserve max size of the Player Vector
			   This is supposed to have a m_Server.GetMaxPlayers() function call
			   but this will be done later. */
			m_Players.reserve(16);

			// Register the packet handler
			m_Server.GetNetwork().Attach(*m_PacketHandler);
		}

		Players::~Players() {
			m_Server.GetNetwork().Detach(*m_PacketHandler);
		}

		Player* Players::GetPlayer(const Network::IClientID &clientId) {
			for (std::unique_ptr<Player> &player : m_Players)
			if (*player->ClientID == clientId)
				return player.get();

			// Not found, return null instead
			return nullptr;
		}

		void Players::JoinPlayer(const Network::IClientID &clientId) {
			// Log Incoming Player
			m_Logger.LogHighlight("New Player (%s) Attempting Join", clientId.ToString().c_str());

			// Send all Unit descs to the Player
			m_Server.GetUnits().SendAllUnitDescs(clientId);

			// Create a new dummy Unit for the Player to use
			std::unique_ptr<Units::DynamicUnit> unit = std::make_unique<Units::DummyUnit>(m_Server.GetPhysics(), 10);

			// TEST: Damage the player
			unit->Damage(2);

			// Add Player to the Vector
			Player *player = new Player(
				clientId,
				*unit
			);
			m_Players.push_back(std::unique_ptr<Player>(player));

			// Send the Player a Player Desc packet
			// Has to be before registering the unit
			m_Dispatcher->SendPlayerDesc(
				*player->ClientID,
				player->Unit.GetHealth(),
				player->Unit.ID
			);

			// Pass the Unit to the Unit Manager
			m_Server.GetUnits().AddUnit(std::move(unit));

			// Invoke Event
			OnPlayerJoined.Invoke(*player);

			// And Log it
			m_Logger.LogHighlight("New Player (%s) Joined World", clientId.ToString().c_str());
		}

		void Players::RemovePlayer(const Network::IClientID &clientId) {
			// Find and Remove Player
			unsigned int unitId = 0;
			std::vector<std::unique_ptr<Player>>::iterator it = m_Players.begin();
			while (it != m_Players.end()) {
				if (*(*it)->ClientID == clientId) {
					// Found it!
					unitId = (*it)->Unit.ID;
					it = m_Players.erase(it);
					break;
				}
				else
					++it;
			}

			// Remove Player Unit
			m_Server.GetUnits().RemoveUnit(unitId);

			// And Log it
			m_Logger.LogHighlight("Player (%s) Parted World", clientId.ToString().c_str());
		}

		// Network Callback Functions

		void Players::ReceivedPlayerDisconnected(const Network::IClientID &clientId) {
			// Make sure the client isn't doing something weird
			if (!GetPlayer(clientId)) {
				/* Report packet error here */
				return;
			}

			// Remove Player
			RemovePlayer(clientId);
		}

		void Players::ReceivedPlayerPhysicsUpdate(const Network::IClientID &clientId, CNetwork::PhysicsUpdateData physicsData) {
			// Retrieve the Player Object by ID
			Player *player = GetPlayer(clientId);

			// Make sure the client isn't doing something weird
			if (!player) {
				/* Report packet error here */
				return;
			}

			// Set Data
			player->Unit.ReceivedPhysicsUpdate(std::move(physicsData));
		}
	}
}