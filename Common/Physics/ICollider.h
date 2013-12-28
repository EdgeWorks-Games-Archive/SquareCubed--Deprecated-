#pragma once

namespace Physics {
	struct AABBData;
	class Physics;
	class IRigidBody;

	class ICollider {
	public:
		virtual ~ICollider() {}
	
	protected: // Protected Broadphase Data Helpers
		friend class IRigidBody;
		virtual void UpdateBroadphaseAABB(IRigidBody &rigidBody) = 0;
	};
}