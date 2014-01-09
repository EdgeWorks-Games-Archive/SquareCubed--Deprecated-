#pragma once

#include "DataTypes.h"

namespace Physics {
	class IRigidBody;

	class ICollider {
	public:
		AABBData BroadphaseAABB;
		float BroadphaseRadius;

	public:
		virtual ~ICollider() {}
		virtual void UpdateBroadphaseData(IRigidBody &rigidBody) = 0;
	};
}