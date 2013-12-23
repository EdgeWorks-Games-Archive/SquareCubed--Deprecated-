#pragma once

#include "IClientID.h"

#include <CommonLib/agenttypes.h>

namespace Server {
	namespace Network {
		class IPlayerDispatcher {
		public: // Initialization/Uninitialization
			virtual ~IPlayerDispatcher() {}

		public: // Send Functions
			virtual void SendPlayerDesc(const IClientID &clientId, DataTypes::Health health, unsigned int agentId) = 0;
		};
	}
}