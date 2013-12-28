#pragma once

#include "IClientID.h"
#include <CommonLib/PhysicsPacketDataTypes.h>

namespace Server {
	namespace Players { struct Player; }

	namespace Network {
		class IDebugCallback {
		public: // Initialization/Uninitialization
			virtual ~IDebugCallback() {}

		public: // Callback Functions
			virtual void ReceivedSpawnUnit(glm::vec2 pos) = 0;
		};
	}
}