#include "AABBBroadphase.h"

#include "DynamicRigidBody.h"
#include "CollisionResolver.h"

namespace Physics {
	// Broadphase Collection

	void AABBBroadphase::DetectCollision(const std::list<std::reference_wrapper<DynamicRigidBody>> &dynamicRigidBodies, const CollisionResolver &resolver) {
		// If there's objects to iterate through
		if (dynamicRigidBodies.size() > 1) {
			// Iterate till one object before the last one
			auto end = std::prev(dynamicRigidBodies.end(), 1);
			for (auto rigidBodyAit = dynamicRigidBodies.begin(); rigidBodyAit != end; rigidBodyAit++) {
				// We only need to iterate through every combination
				// once, so rather then a normal stacked loop we're
				// starting the internal loop at the current iterator + 1
				for (auto rigidBodyBit = std::next(rigidBodyAit, 1); rigidBodyBit != dynamicRigidBodies.end(); rigidBodyBit++) {
					// Ignore if same RigidBody
					if (rigidBodyAit != rigidBodyBit) {
						// Check if Broadphase AABBs intersect
						if (rigidBodyAit->get().BroadphaseAABB.Intersects(rigidBodyBit->get().BroadphaseAABB)) {
							// Commenting this out probably nukes the
							// entire thing in optimization.
							//printf("Intersection!\n");
						}
					}
				}
			}
		}
	}
}