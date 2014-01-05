#include "DynamicRigidBody.h"

#include <algorithm>

namespace Physics {
	void DynamicRigidBody::UpdatePhysics(const float delta) {
		// Calculate Velocity Per Second Change Needed
		glm::vec2 velocityChange = TargetVelocity - Velocity;

		// Clamp Velocity Change per Current Delta
		float sqVelChange = (velocityChange.x * velocityChange.x) + (velocityChange.y * velocityChange.y);
		float maxVelChange = MaxVelocityChange * delta;
		if (sqVelChange > (maxVelChange * maxVelChange)) {
			// Exceeds, Calculate new Velocity in same Direction
			velocityChange = glm::normalize(velocityChange) * maxVelChange;
		}

		// Increase Velocity
		Velocity += std::move(velocityChange);

		// Calculate new Position
		Position += Velocity * delta;

		// Update Broadphase Data
		UpdateBroadphase();
	}

	void DynamicRigidBody::ResolveCollisions() {
	}
}