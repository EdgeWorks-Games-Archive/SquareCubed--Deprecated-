#pragma once

#include "IBroadphase.h"

namespace Physics {
	/** Axis Aligned Bounding Box broadphase algorithm class.
	 * Implements IBroadphase and provides an AABB approach to
	 * broadphase collection. It uses axis aligned bounding
	 * boxes to find potential collisions.
	 */
	class AABBBroadphase final : public IBroadphase {
	protected: // Broadphase Collection
		void DetectCollision(const std::list<std::reference_wrapper<DynamicRigidBody>> &dynamicRigidBodies, const CollisionResolver &resolver);
	};
}