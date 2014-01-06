#pragma once

#include "IRigidBody.h"

namespace Physics {
	class DynamicRigidBody final : public IRigidBody {
	public:
		glm::vec2 Velocity;
		glm::vec2 TargetVelocity;
		float MaxVelocityChange;

	public:
		DynamicRigidBody(std::unique_ptr<ICollider> collider, const float maxVelocityChange) :
			IRigidBody(std::move(collider)),
			Velocity(),
			TargetVelocity(),
			MaxVelocityChange(maxVelocityChange)
		{}

	public:
		void UpdateVelocity(const float delta, Physics &physics);
		void UpdatePosition(const float delta);
		void ResolveCollisions();
	};
}