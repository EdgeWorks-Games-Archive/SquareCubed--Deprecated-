#pragma once

#include "DataTypes.h"
#include "Types.h"

#include <memory>

namespace Physics {
	class IRigidBody {
	public:
		glm::vec2 Position;
		std::unique_ptr<ICollider> Collider;

		IRigidBody(std::unique_ptr<ICollider> collider);
		virtual ~IRigidBody();
	};
}