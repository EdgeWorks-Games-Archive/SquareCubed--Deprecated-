#pragma once

#include <CommonLib/unittypes.h>

namespace CNetwork { struct PhysicsUpdateData; }

namespace Network {
	class IUnitsCallback {
	public: // Initialization/Uninitialization
		virtual ~IUnitsCallback() {}

	public: // Callback Functions
		virtual void ReceivedUpdateUnitPhysics(const unsigned int unitId, const CNetwork::PhysicsUpdateData &data) = 0;
		virtual void ReceivedUnitDesc(unsigned int unitId, DataTypes::Health health, unsigned int graphicId) = 0;
		virtual void ReceivedRemoveUnit(unsigned int unitId) = 0;
	};
}