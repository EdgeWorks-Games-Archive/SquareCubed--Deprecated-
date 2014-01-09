#pragma once

#include "IBroadphase.h"

namespace Physics {
	/** Axis Aligned Bounding Box broadphase algorithm class.
	 * Implements IBroadphase and provides an AABB approach to
	 * broadphase collection. It uses axis aligned bounding
	 * boxes to find potential collisions.
	 */
	class AABBBroadphase final : public IBroadphase {
	public: // Broadphase Collection
		std::list<std::reference_wrapper<DynamicRigidBody>> DetectDynamicCollisions(const DynamicRigidBody &dynamicRigidBody, Physics &physics);
	};
}