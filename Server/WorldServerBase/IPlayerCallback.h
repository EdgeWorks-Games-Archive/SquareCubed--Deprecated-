#pragma once

#include "IClientID.h"
#include <CommonLib/PhysicsPacketDataTypes.h>

namespace Server {
	namespace Players { struct Player; }

	namespace Network {
		class IPlayerCallback {
		public: // Initialization/Uninitialization
			virtual ~IPlayerCallback() {}

		public: // Callback Functions
			virtual void JoinPlayer(const IClientID &clientId) = 0;

			virtual void ReceivedPlayerDisconnected(const IClientID &clientId) = 0;
			virtual void ReceivedPlayerPhysicsUpdate(const IClientID &clientId, CNetwork::PhysicsUpdateData physicsData) = 0;
		};
	}
}