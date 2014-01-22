#pragma once

#include "Unit.h"
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

			std::list<std::unique_ptr<Unit>> m_Units;

		public: // Initialization/Uninitialization
			Units(Core::WorldServer &server);
			~Units();

		public: // Unit Management Functions
			/** Adds an unit to the class.
			 * Adding an unit means it gets updated and synced.
			 * \param[in]	unit	The unit to add.
			 */
			void AddUnit(std::unique_ptr<Unit> unit);

			/** Removes an unit from the class.
			 * Also deconstructs the unit.
			 * \param[in]	unitId	The ID of the unit to delete.
			 */
			void RemoveUnit(unsigned int unitId);

			/** Looks up the unit with the specified ID.
			 * \param[in]	unitId	The unit ID to look up.
			 * \return		The requested unit or nullptr if not found.
			 */
			Unit* GetUnit(unsigned int unitId);

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