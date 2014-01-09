#pragma once

#include "IRigidBody.h"

namespace Physics {
	class Physics;
	class ICollider;

	class DynamicRigidBody final : public IRigidBody {
	public:
		glm::vec2 Velocity;
		glm::vec2 TargetVelocity;
		float MaxVelocityChange;

	public:
		DynamicRigidBody(std::unique_ptr<ICollider> collider, const float maxVelocityChange);
		~DynamicRigidBody();

	public:
		void UpdateVelocity(const float delta, Physics &physics);
		void UpdatePosition(const float delta);
		void ResolveCollisions();
	};
}