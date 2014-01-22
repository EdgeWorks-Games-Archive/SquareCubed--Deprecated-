#include "IRigidBody.h"

#include "ICollider.h"

namespace Physics {
	IRigidBody::IRigidBody(std::unique_ptr<ICollider> collider) :
		Position(),
		Collider(std::move(collider))
	{}

	IRigidBody::~IRigidBody() {}
}