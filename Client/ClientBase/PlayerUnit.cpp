#include "PlayerUnit.h"

namespace Tools {
	namespace Units {
		void PlayerUnit::ReceivedUpdatePhysics(const CNetwork::PhysicsUpdateData &data) {
			/* Nothing, player unit doesn't listen to packets */
		}
	}
}