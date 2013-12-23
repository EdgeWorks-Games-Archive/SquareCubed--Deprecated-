#include "IRigidBody.h"

namespace Physics {
	void IRigidBody::UpdateBroadphase() {
		pm_Collider->UpdateBroadphaseAABB(*this);
	}
}