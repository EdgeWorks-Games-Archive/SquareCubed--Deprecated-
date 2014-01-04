#include "BaseUnitTypes.h"

#include <CommonLib/PhysicsPacketDataTypes.h>

namespace Tools {
	namespace Units {
		void DynamicUnit::ReceivedUpdatePhysics(const CNetwork::PhysicsUpdateData &data) {
			RigidBody.Position = data.Position;
			Rotation.Radians = data.Rotation;
			RigidBody.Velocity = data.Velocity;
			RigidBody.TargetVelocity = data.TargetVelocity;
		}
	}
}