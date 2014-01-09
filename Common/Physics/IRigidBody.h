#pragma once

#include "DataTypes.h"

#include <memory>

namespace Physics {
	class ICollider;

	class IRigidBody {
	public:
		glm::vec2 Position;
		std::unique_ptr<ICollider> Collider;

		IRigidBody(std::unique_ptr<ICollider> collider);
		virtual ~IRigidBody();
	};
}