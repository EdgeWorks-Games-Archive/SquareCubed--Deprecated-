#include "UnitSelect.h"

#include "Units.h"
#include "BaseUnitTypes.h"
#include "MoveTask.h"

#include "WorldServer.h"
#include "INetwork.h"
#include "INetworkFactory.h"
#include "IPacketHandler.h"

namespace Server {
	namespace Units {
		UnitSelect::UnitSelect(Core::WorldServer &server, Units &units) :
			m_Units(units),
			m_Server(server),
			m_PacketHandler(server.GetNetwork().GetFactory().CreateUnitSelectHandler(*this))
		{
			m_Server.GetNetwork().Attach(*m_PacketHandler);
		}

		UnitSelect::~UnitSelect() {
			m_Server.GetNetwork().Detach(*m_PacketHandler);
		}

		void UnitSelect::ReceivedUnitOrder(unsigned int unitId, glm::vec2 pos) {
			// Get the Unit associated with the ID
			Unit *unit = m_Units.GetUnit(unitId);
			if (unit == nullptr) {
				// TODO: Log invalid ID
				return;
			}

			// Cast the Unit to the Required Type
			AIUnit *aiUnit = dynamic_cast<AIUnit*>(unit);
			if (aiUnit == nullptr) {
				// TODO: Log invalid Unit Type
				return;
			}

			// Do the actual task
			aiUnit->SetTask(std::make_unique<AI::MoveTask>(pos, 2.0f));
		}
	}
}