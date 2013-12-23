#pragma once

#include "IClientID.h"

#include <CommonLib/agenttypes.h>
#include <Physics/DynamicRigidBody.h>

namespace Server {
	namespace Network {
		class IAgentsDispatcher {
		public: // Initialization/Uninitialization
			virtual ~IAgentsDispatcher() {}

		public: // Send Functions
			virtual void BroadcastAgentPhysics(const unsigned int agentId, const Physics::DynamicRigidBody &rigidBody, const float rotation) = 0;
			virtual void BroadcastAgentDesc(unsigned int agentId, DataTypes::Health health, unsigned int graphicId) = 0;
			virtual void BroadcastAgentRemove(unsigned int agentId) = 0;
			virtual void SendAgentDesc(const IClientID &clientId, unsigned int agentId, DataTypes::Health health, unsigned int graphicId) = 0;
		};
	}
}