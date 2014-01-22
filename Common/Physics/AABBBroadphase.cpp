#include "AABBBroadphase.h"

#include "Physics.h"
#include "DynamicRigidBody.h"
#include "ICollider.h"

namespace Physics {
	// Broadphase Collection

	std::list<std::reference_wrapper<DynamicRigidBody>> AABBBroadphase::DetectDynamicCollisions(const DynamicRigidBody &rigidBodyA, Physics &physics) {
		std::list<std::reference_wrapper<DynamicRigidBody>> retList;
		for (DynamicRigidBody &rigidBodyB : physics.GetAllDynamic()) {
			if (&rigidBodyA != &rigidBodyB) {
				if (rigidBodyA.Collider->BroadphaseAABB.Intersects(rigidBodyB.Collider->BroadphaseAABB)) {
					retList.push_back(rigidBodyB);
				}
			}
		}
		return retList;
	}
}