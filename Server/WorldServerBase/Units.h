#pragma once

#include "IUnit.h"
#include "IClientID.h"

#include <list>
#include <memory>

namespace Server {
	namespace Core { class WorldServer; }
	namespace Network { class IUnitsDispatcher; }

	namespace Units {
		class Units final {
			Core::WorldServer &m_Server;
			std::unique_ptr<Network::IUnitsDispatcher> m_Dispatcher;

			std::list<std::unique_ptr<IUnit>> m_Units;

		public: // Initialization/Uninitialization
			Units(Core::WorldServer &server);
			~Units();

		public: // Unit Management Functions
			/** Adds an unit to the class.
			 * Adding an unit means it gets updated and synced.
			 */
			void AddUnit(std::unique_ptr<IUnit> unit);

			/** Removes an unit from the class.
			 * Also deconstructs the unit.
			 */
			void RemoveUnit(unsigned int unitId);

		public: // Networking Functions
			/** Sends all unit descriptors to the client. */
			void SendAllUnitDescs(const Network::IClientID &clientId);

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