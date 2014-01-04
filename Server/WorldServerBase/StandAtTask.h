#pragma once

#include "ITask.h"

#include <glm/glm.hpp>

namespace Server {
	namespace Units {
		namespace AI {
			class StandAtTask final : public ITask {
				glm::vec2 m_Target;
				float m_SqrSlowdownDistance; // < Square Slowdown Distance
				float m_InvSqrSlowdownDistance; // < Inverse Square Slowdown Distance

			public:
				float Deadzone;
				float Speed;
				
				StandAtTask(glm::vec2 target, float speed);

				void SetSlowdownDistance(float slowdownDistance);

				void Update(const float delta, AIUnit &unit);
			};
		}
	}
}