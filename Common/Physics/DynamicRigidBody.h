#pragma once

#include "IRigidBody.h"

namespace Physics {
	class DynamicRigidBody final : public IRigidBody {
	public:
		MassData m_MassData;
		glm::vec2 Velocity;
		glm::vec2 Force;

	public:
		DynamicRigidBody(std::unique_ptr<ICollider> collider, const float mass) :
			IRigidBody(std::move(collider)),
			m_MassData(mass),
			Velocity(),
			Force()
		{}

	public:
		void UpdatePhysics(const float delta);
		void ResolveCollisions();
	};
}