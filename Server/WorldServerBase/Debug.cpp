#ifdef _DEBUG

#include "Debug.h"
#include "BaseUnitTypes.h"

#include "WorldServer.h"
#include "INetwork.h"
#include "INetworkFactory.h"

#include <CommonLib/ILoggingManager.h>

namespace Server {
	namespace Debug {
		Debug::Debug(Core::WorldServer &server, Units::Units &units) :
			m_Server(server),
			m_Units(units),
			m_PacketHandler(server.GetNetwork().GetFactory().CreateDebugHandler(*this)),
			m_Logger(server.GetLoggingManager().CreateLogger("Debug"))
		{
			m_Server.GetNetwork().Attach(*m_PacketHandler);
		}

		Debug::~Debug() {
			m_Server.GetNetwork().Detach(*m_PacketHandler);
		}

		void Debug::ReceivedSpawnUnit(glm::vec2 pos) {
			std::unique_ptr<Units::DynamicUnit> unit = std::make_unique<Units::DynamicUnit>(m_Server.GetPhysics(), 10, 2.0f);
			unit->SetPosition(pos);
			m_Units.AddUnit(std::move(unit));
			m_Logger.LogInfo("Spawning unit at %f, %f.", pos.x, pos.y);
		}
	}
}

#endif