#include "DynamicRigidBody.h"

#include "Physics.h"
#include "IBroadphase.h"

#include <algorithm>

namespace Physics {
	void DynamicRigidBody::UpdateVelocity(const float delta, Physics &physics) {
		// Calculate Velocity Per Second Change Needed
		glm::vec2 velocityChange = TargetVelocity - Velocity;

		// Add Velocity Caused by Nearby Pushing Rigidbodies
		// Note: this might cause some problems with the player rigidbody
		for (DynamicRigidBody &rigidBody : physics.GetBroadphase().DetectCollisions(*this, physics)) {
			// Check if the Distance is smaller than the two radii combined
			glm::vec2 diff = Position - rigidBody.Position;
			if ((diff.x * diff.x) + (diff.y * diff.y) < (BroadphaseRadius + rigidBody.BroadphaseRadius) * (BroadphaseRadius + rigidBody.BroadphaseRadius)) {
				// If diff is 0, glm::normalize will crash
				if (diff.x == 0.0f && diff.y == 0.0f)
					diff.x = this > &rigidBody ? 1.0f : -1.0f;

				// Calculate the force with which to push us a bit away
				velocityChange += glm::normalize(diff) * (16.0f * delta);
			}
		}

		// Clamp Velocity Change per Current Delta
		float sqVelChange = (velocityChange.x * velocityChange.x) + (velocityChange.y * velocityChange.y);
		float maxVelChange = MaxVelocityChange * delta;
		if (sqVelChange > (maxVelChange * maxVelChange)) {
			// Exceeds, Calculate new Velocity in same Direction
			velocityChange = glm::normalize(velocityChange) * maxVelChange;
		}

		// Calculate new Velocity
		Velocity += std::move(velocityChange);
		
		// Update Broadphase Data
		UpdateBroadphase();
	}

	void DynamicRigidBody::UpdatePosition(const float delta) {
		Position += Velocity * delta;
	}

	void DynamicRigidBody::ResolveCollisions() {
	}
}