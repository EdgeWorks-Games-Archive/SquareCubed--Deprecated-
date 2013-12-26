#pragma once

#include "BaseUnitTypes.h"

namespace Tools {
	namespace Units {
		class PlayerUnit final : public PhysicsUnit {
		public:
			PlayerUnit(UnitID id, DataTypes::Health health, Physics::Physics &physics) : PhysicsUnit(id, std::move(health), physics) {}
			void ReceivedUpdatePhysics(const CNetwork::PhysicsUpdateData &data);
		};
	}
}