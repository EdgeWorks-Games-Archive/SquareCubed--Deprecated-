#pragma once

#include "ITask.h"

#include <glm/glm.hpp>

namespace Server {
	namespace Units {
		namespace AI {
			class StandAtTask final : public ITask {
				glm::vec2 m_Target;
				glm::vec2 m_Velocity;

			public:
				float Deadzone;

				StandAtTask(glm::vec2 target);
				void Update(const float delta, AIUnit &unit);
			};
		}
	}
}