#pragma once

#include "IUnitSelectCallback.h"
#include "Unit.h"

namespace Server {
	namespace Core { class WorldServer; }

	namespace Network {
		class IPacketHandler;
	}

	namespace Units {
		class Units;

		class UnitSelect final : Network::IUnitSelectCallback {
			Units &m_Units;
			Core::WorldServer &m_Server;
			std::unique_ptr<Network::IPacketHandler> m_PacketHandler;
		
		public: // Initialization/Uninitialization
			UnitSelect(Core::WorldServer &server, Units &units);
			~UnitSelect();

		public: // Unit Management Functions
			// Sets a Unit's task
			void ReceivedUnitOrder(unsigned int unitId, glm::vec2 pos);
		};
	}
}