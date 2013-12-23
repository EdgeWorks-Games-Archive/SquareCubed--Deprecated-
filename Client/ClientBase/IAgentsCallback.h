#pragma once

#include <CommonLib/agenttypes.h>

namespace CNetwork { struct PhysicsUpdateData; }

namespace Network {
	class IAgentsCallback {
	public: // Initialization/Uninitialization
		virtual ~IAgentsCallback() {}

	public: // Callback Functions
		virtual void ReceivedUpdateAgentPhysics(const unsigned int agentId, const CNetwork::PhysicsUpdateData &data) = 0;
		virtual void ReceivedAgentDesc(unsigned int agentId, DataTypes::Health health, unsigned int graphicId) = 0;
		virtual void ReceivedRemoveAgent(unsigned int agentId) = 0;
	};
}