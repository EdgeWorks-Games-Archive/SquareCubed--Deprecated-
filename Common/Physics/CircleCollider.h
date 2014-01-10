#pragma once

#include "ICollider.h"

namespace Physics {
	class CircleCollider : public ICollider {
	public:
		float Radius;

	public:
		CircleCollider(const float radius) :
			Radius(radius)
		{}

	protected:
		void UpdateBroadphaseData(IRigidBody &rigidBody);
	};
}