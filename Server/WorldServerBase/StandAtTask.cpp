#include "StandAtTask.h"

#include "BaseUnitTypes.h"

#include <CommonLib/postypes.h>

namespace Server {
	namespace Units {
		namespace AI {
			StandAtTask::StandAtTask(glm::vec2 target) :
				m_Target(std::move(target)),
				m_Velocity(),
				Deadzone(0.1f)
			{}

			void StandAtTask::Update(const float, AIUnit &unit) {
				if (fabs(unit.RigidBody.Position.x - m_Target.x) > Deadzone ||
					fabs(unit.RigidBody.Position.y - m_Target.y) > Deadzone) {
					// Calculate Angle
					Anglef angle = atan2f(m_Target.x - unit.RigidBody.Position.x, m_Target.y - unit.RigidBody.Position.y);

					// Scale Input
					m_Velocity.x = angle.GetSin();
					m_Velocity.y = angle.GetCos();

					// TODO: Hack to get this working for now
					unit.RigidBody.Velocity = glm::vec2(m_Velocity.x, m_Velocity.y);
				}
				else
					unit.RigidBody.Velocity = glm::vec2(0, 0);
			}
		}
	}
}