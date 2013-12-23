#pragma once

#include "Collider.h"
#include "DataTypes.h"

namespace Physics {
	class CircleCollider : public Collider {
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