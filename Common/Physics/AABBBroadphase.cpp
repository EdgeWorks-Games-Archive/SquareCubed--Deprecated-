#include "AABBBroadphase.h"

#include "Physics.h"
#include "DynamicRigidBody.h"

namespace Physics {
	// Broadphase Collection

	std::list<std::reference_wrapper<DynamicRigidBody>> AABBBroadphase::DetectCollisions(const DynamicRigidBody &rigidBodyA, Physics &physics) {
		std::list<std::reference_wrapper<DynamicRigidBody>> retList;
		for (DynamicRigidBody &rigidBodyB : physics.GetAllDynamic()) {
			if (&rigidBodyA != &rigidBodyB) {
				if (rigidBodyA.BroadphaseAABB.Intersects(rigidBodyB.BroadphaseAABB)) {
					retList.push_back(rigidBodyB);
				}
			}
		}
		return retList;
	}
}