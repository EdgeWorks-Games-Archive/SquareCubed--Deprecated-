#pragma once

#include "IClientID.h"

#include <CommonLib/unittypes.h>

namespace Server {
	namespace Network {
		class IPlayerDispatcher {
		public: // Initialization/Uninitialization
			virtual ~IPlayerDispatcher() {}

		public: // Send Functions
			virtual void SendPlayerDesc(const IClientID &clientId, DataTypes::Health health, unsigned int unitId) = 0;
		};
	}
}