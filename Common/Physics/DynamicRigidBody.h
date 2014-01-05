#pragma once

#include "IRigidBody.h"

namespace Physics {
	class DynamicRigidBody final : public IRigidBody {
	public:
		float MaxVelocityChange;
		glm::vec2 Velocity;
		glm::vec2 TargetVelocity;

	public:
		DynamicRigidBody(std::unique_ptr<ICollider> collider, const float maxVelocityChange) :
			IRigidBody(std::move(collider)),
			MaxVelocityChange(maxVelocityChange),
			Velocity(),
			TargetVelocity()
		{}

	public:
		void UpdateVelocity(const float delta, Physics &physics);
		void UpdatePosition(const float delta);
		void ResolveCollisions();
	};
}