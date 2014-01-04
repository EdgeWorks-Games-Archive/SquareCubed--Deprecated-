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
				SlowdownDistance(0.5f)
			{}

			void StandAtTask::Update(const float, AIUnit &unit) {
				// This whole function needs a lot of optimization, for now it's
				// written like this because this bit is still a work in progress.
				glm::vec2 posDiff(m_Target.x - unit.RigidBody.Position.x, m_Target.y - unit.RigidBody.Position.y);
				if (fabs(posDiff.x) > Deadzone || fabs(posDiff.y) > Deadzone) {
					// Calculate Angle
					Anglef angle = atan2f(posDiff.x, posDiff.y);

					// Prepare to Resolve Target Velocity
					glm::vec2 tarVel;

					// Make sure Unit Slows down a bit in Advance
					// TODO: Improve so rather than doing it on an axis by axis basis it's done with the real distance.
					float distance = sqrtf(pow(fabs(posDiff.x), 2) + pow(fabs(posDiff.y), 2));
					if (distance < SlowdownDistance) {
						tarVel.x = angle.GetSin() * Speed * distance / SlowdownDistance;
						tarVel.y = angle.GetCos() * Speed * distance / SlowdownDistance;
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