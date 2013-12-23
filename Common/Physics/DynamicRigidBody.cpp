#include "DynamicRigidBody.h"

namespace Physics {
	void DynamicRigidBody::UpdatePhysics(const float delta) {
		// Calculate velocity change
		glm::vec2 velocityChange = m_MassData.GetInverseMass() * Force * delta;

		// Calculate friction and apply to velocity change
		// 8.0f is just a random picked constant that ended up well.
		// If you want the physics to be less 'floaty', increase it.
		// Increasing this constant severely impacts the effect of forces.
		velocityChange -= Velocity * 8.0f * delta;

		// Calculate new position
		Position += (Velocity + (velocityChange * 0.5f)) * delta;

		// Set increased velocity
		Velocity += std::move(velocityChange);

		// Update Broadphase Data
		UpdateBroadphase();
	}

	void DynamicRigidBody::ResolveCollisions() {
	}
}