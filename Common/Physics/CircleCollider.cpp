#include "CircleCollider.h"

#include "IRigidBody.h"

namespace Physics {
	void CircleCollider::UpdateBroadphaseAABB(IRigidBody &rigidBody) {
		rigidBody.BroadphaseAABB.Min.x = rigidBody.Position.x - Radius;
		rigidBody.BroadphaseAABB.Min.y = rigidBody.Position.y - Radius;
		rigidBody.BroadphaseAABB.Max.x = rigidBody.Position.x + Radius;
		rigidBody.BroadphaseAABB.Max.y = rigidBody.Position.y + Radius;
		rigidBody.BroadphaseRadius = Radius;
	}
}