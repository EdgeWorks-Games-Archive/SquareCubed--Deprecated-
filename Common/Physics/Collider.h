#pragma once

namespace Physics {
	struct AABBData;
	class Physics;
	class IRigidBody;

	class Collider {
	public:
		virtual ~Collider() {}
	
	protected: // Protected Broadphase Data Helpers
		friend class IRigidBody;
		virtual void UpdateBroadphaseAABB(IRigidBody &rigidBody) = 0;
	};
}