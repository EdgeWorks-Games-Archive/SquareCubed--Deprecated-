#pragma once

#include <glm/glm.hpp>

namespace CNetwork {
	struct PhysicsUpdateData {
		// Position Sync Data
		glm::vec2 Position;
		float Rotation;

		// Physics Sync Data
		glm::vec2 Velocity;
		glm::vec2 TargetVelocity;
	};
}