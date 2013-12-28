#pragma once

#include "ICollider.h"
#include "DataTypes.h"

namespace Physics {
	class CircleCollider : public ICollider {
	public:
		float Radius;

	public:
		CircleCollider(const float radius) :
			Radius(radius)
		{}

	protected:
		void UpdateBroadphaseAABB(IRigidBody &rigidBody);
	};
}