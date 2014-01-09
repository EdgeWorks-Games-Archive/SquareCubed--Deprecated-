#include "CircleCollider.h"

#include "IRigidBody.h"

namespace Physics {
	void CircleCollider::UpdateBroadphaseData(IRigidBody &rigidBody) {
		BroadphaseAABB.Min.x = rigidBody.Position.x - Radius;
		BroadphaseAABB.Min.y = rigidBody.Position.y - Radius;
		BroadphaseAABB.Max.x = rigidBody.Position.x + Radius;
		BroadphaseAABB.Max.y = rigidBody.Position.y + Radius;
		BroadphaseRadius = Radius;
	}
}