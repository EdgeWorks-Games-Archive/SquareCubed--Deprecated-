#pragma once

#ifdef _DEBUG

#include "IDebugCallback.h"
#include "Units.h"
#include "Types.h"
#include "IPacketHandler.h"

#include <CommonLib/Logger.h>

namespace Server {
	namespace Debug {
		class Debug : public Network::IDebugCallback {
			Core::WorldServer &m_Server;
			Units::Units &m_Units;
			std::unique_ptr<Network::IPacketHandler> m_PacketHandler;
			Utils::Logger m_Logger;

		public:
			Debug(Core::WorldServer &server, Units::Units &units);
			~Debug();
			void ReceivedSpawnUnit(glm::vec2 pos);
		};
	}
}

#endif