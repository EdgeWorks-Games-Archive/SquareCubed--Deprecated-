#pragma once

#include "Types.h"

#include <glm/glm.hpp>

namespace Server {
	namespace Units {
		namespace AI {
			class MoveBehavior final {
				glm::vec2 m_Target;
				bool m_Enabled;

				float m_SqrSlowdownDistance; // < Square Slowdown Distance
				float m_InvSlowdownDistance; // < Inverse Slowdown Distance

			public: // Properties
				float Deadzone;
				float Speed;
				void SetSlowdownDistance(float slowdownDistance);
				
			public: // Initialization/Uninitialization
				MoveBehavior(float speed);

			public: // Helper Functions
				void MoveTo(glm::vec2 target);
				
			public: // Game Loop
				void Update(const float delta, AIUnit &unit);
			};
		}
	}
}