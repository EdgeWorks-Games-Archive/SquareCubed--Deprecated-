#pragma once

#include "ITask.h"

#include <glm/glm.hpp>

namespace Server {
	namespace Units {
		namespace AI {
			class StandAtTask final : public ITask {
				glm::vec2 m_Target;

			public:
				float Deadzone;
				float Speed;
				/** The unit will start slowing down if the unit is this far away from the target. */
				float SlowdownDistance;

				StandAtTask(glm::vec2 target, float speed);
				void Update(const float delta, AIUnit &unit);
			};
		}
	}
}