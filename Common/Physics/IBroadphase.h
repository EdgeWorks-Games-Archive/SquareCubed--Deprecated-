#pragma once

#include <list>

namespace Physics {
	class Physics;
	class DynamicRigidBody;
	class CollisionResolver;

	/** Broadphase base interface.
	 */
	class IBroadphase {
	public: // Initialization/Uninitialization
		virtual ~IBroadphase() {}

	protected: // Broadphase Collection
		friend class Physics;
		virtual void DetectCollision(const std::list<std::reference_wrapper<DynamicRigidBody>> &dynamicRigidBodies, const CollisionResolver &resolver) = 0;

	protected: // Physics Data Linking Function
		void SetParent(Physics &physics);
	};
}