#pragma once

#include <list>
#include <memory>

namespace Physics {
	class Physics;
	class DynamicRigidBody;

	/** Broadphase base interface.
	 */
	class IBroadphase {
	public: // Initialization/Uninitialization
		virtual ~IBroadphase() {}

	public: // Broadphase Collection
		friend class Physics;
		virtual std::list<std::reference_wrapper<DynamicRigidBody>> DetectCollisions(const DynamicRigidBody &dynamicRigidBody, Physics &physics) = 0;
	};
}