#pragma once

#include "BaseAgentTypes.h"

namespace Tools {
	namespace Agents {
		class PlayerAgent final : public PhysicsAgent {
		public:
			PlayerAgent(AgentID id, DataTypes::Health health, Physics::Physics &physics) : PhysicsAgent(id, std::move(health), physics) {}
			void ReceivedUpdatePhysics(const CNetwork::PhysicsUpdateData &data);
		};
	}
}