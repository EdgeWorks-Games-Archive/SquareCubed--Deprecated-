#pragma once

#include "BaseUnitTypes.h"

namespace Tools {
	namespace Units {
		class PlayerUnit final : public DynamicUnit {
		public:
			PlayerUnit(UnitID id, DataTypes::Health health, Physics::Physics &physics) : DynamicUnit(id, std::move(health), physics) {}
			void ReceivedUpdatePhysics(const CNetwork::PhysicsUpdateData &data);
		};
	}
}