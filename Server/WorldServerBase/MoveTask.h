#pragma once

#include "ITask.h"

#include <glm/glm.hpp>

namespace Server {
	namespace Units {
		namespace AI {
			class MoveTask final : public ITask {
				glm::vec2 m_Target;
				float m_SqrSlowdownDistance; // < Square Slowdown Distance
				float m_InvSlowdownDistance; // < Inverse Slowdown Distance

			public:
				float Deadzone;
				float Speed;
				
				MoveTask(glm::vec2 target, float speed);

				void SetSlowdownDistance(float slowdownDistance);

				void Update(const float delta, AIUnit &unit);
			};
		}
	}
}