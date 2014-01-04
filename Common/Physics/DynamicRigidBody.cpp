#include "DynamicRigidBody.h"

#include <algorithm>

namespace Physics {
	void DynamicRigidBody::UpdatePhysics(const float delta) {
		// Calculate Velocity Per Second Change Needed
		glm::vec2 velocityChange = TargetVelocity - Velocity;

		// Clamp Velocity Change Per Second
		// TODO: Calculate for both axis total rather than the two separate
		float maxVelChange = MaxVelocityChange * delta;
		if (velocityChange.x > maxVelChange)
			velocityChange.x = maxVelChange;
		else if (velocityChange.x < -maxVelChange)
			velocityChange.x = -maxVelChange;

		if (velocityChange.y > maxVelChange)
			velocityChange.y = maxVelChange;
		else if (velocityChange.y < -maxVelChange)
			velocityChange.y = -maxVelChange;

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