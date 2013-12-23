#include "BaseAgentTypes.h"

#include <CommonLib/PhysicsPacketDataTypes.h>

namespace Tools {
	namespace Agents {
		void PhysicsAgent::ReceivedUpdatePhysics(const CNetwork::PhysicsUpdateData &data) {
			RigidBody.Position = data.Position;
			RigidBody.Force = data.Force;
			RigidBody.Velocity = data.Velocity;
			Rotation.Radians = data.Rotation;
		}
	}
}