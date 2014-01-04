#include "StandAtTask.h"

#include "BaseUnitTypes.h"

#include <CommonLib/postypes.h>

namespace Server {
	namespace Units {
		namespace AI {
			StandAtTask::StandAtTask(glm::vec2 target, float speed) :
				m_Target(std::move(target)),
				Speed(speed),
				Deadzone(0.1f),
				m_SqrSlowdownDistance(0.5f * 0.5f),
				m_InvSqrSlowdownDistance(1 / m_SqrSlowdownDistance)
			{}

			void StandAtTask::SetSlowdownDistance(float slowdownDistance) {
				m_SqrSlowdownDistance = slowdownDistance * slowdownDistance;
				m_InvSqrSlowdownDistance = 1 / m_SqrSlowdownDistance;
			}

			void StandAtTask::Update(const float, AIUnit &unit) {
				// Calculate Position Difference Data
				glm::vec2 posDiff(m_Target.x - unit.RigidBody.Position.x, m_Target.y - unit.RigidBody.Position.y);
				glm::vec2 absPosDiff(fabs(posDiff.x), fabs(posDiff.y));

				// If we're not there yet
				if (absPosDiff.x > Deadzone || absPosDiff.y > Deadzone) {
					// Calculate Angle
					Anglef angle = atan2f(posDiff.x, posDiff.y);

					// Prepare to Resolve Target Velocity
					glm::vec2 tarVel;

					// Make sure Unit Slows down a bit in Advance
					float sqrDistance = (posDiff.x * posDiff.x) + (posDiff.y * posDiff.y);
					if (sqrDistance < m_SqrSlowdownDistance) {
						tarVel.x = angle.GetSin() * Speed * (sqrDistance * m_InvSqrSlowdownDistance);
						tarVel.y = angle.GetCos() * Speed * (sqrDistance * m_InvSqrSlowdownDistance);
					}
					else {
						tarVel.x = angle.GetSin() * Speed;
						tarVel.y = angle.GetCos() * Speed;
					}

					// Set the Target Velocity
					unit.RigidBody.TargetVelocity = tarVel;

					// Calculate what Rotation to face
					unit.Rotation = -angle.Radians;
				}
				else
					unit.RigidBody.TargetVelocity = glm::vec2(0, 0);
			}
		}
	}
}