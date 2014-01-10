#pragma once

#include "DataTypes.h"
#include "Types.h"

namespace Physics {
	class ICollider {
	public:
		AABBData BroadphaseAABB;
		float BroadphaseRadius;

	public:
		virtual ~ICollider() {}
		virtual void UpdateBroadphaseData(IRigidBody &rigidBody) = 0;
	};
}