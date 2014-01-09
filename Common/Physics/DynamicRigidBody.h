#pragma once

#include "IRigidBody.h"

namespace Physics {
	class Physics;
	class ICollider;

	class DynamicRigidBody final : public IRigidBody {
		Physics &m_Physics;

	public:
		glm::vec2 Velocity;
		glm::vec2 TargetVelocity;
		float MaxVelocityChange;

	public:
		DynamicRigidBody(Physics &physics, std::unique_ptr<ICollider> collider, const float maxVelocityChange);
		~DynamicRigidBody();

	public:
		void UpdateVelocity(const float delta);
		void UpdatePosition(const float delta);
		void ResolveCollisions();
	};
}