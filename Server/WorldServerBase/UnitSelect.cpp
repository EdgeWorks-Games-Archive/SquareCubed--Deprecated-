#include "UnitSelect.h"

#include "Units.h"
#include "BaseUnitTypes.h"
#include "StandAtTask.h"

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
			Unit *unit = m_Units.GetUnit(unitId);
			AIUnit *aiUnit = dynamic_cast<AIUnit*>(unit);
			aiUnit->SetTask(std::make_unique<AI::StandAtTask>(pos, 2.0f));
		}
	}
}