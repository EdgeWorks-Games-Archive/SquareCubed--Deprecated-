#pragma once

#include "IClientID.h"

#include <CommonLib/unittypes.h>
#include <Physics/DynamicRigidBody.h>

namespace Server {
	namespace Network {
		class IUnitsDispatcher {
		public: // Initialization/Uninitialization
			virtual ~IUnitsDispatcher() {}

		public: // Send Functions
			virtual void BroadcastUnitPhysics(const unsigned int unitId, const Physics::DynamicRigidBody &rigidBody, const float rotation) = 0;
			virtual void BroadcastUnitDesc(unsigned int unitId, DataTypes::Health health, unsigned int graphicId) = 0;
			virtual void BroadcastUnitRemove(unsigned int unitId) = 0;
			virtual void SendUnitDesc(const IClientID &clientId, unsigned int unitId, DataTypes::Health health, unsigned int graphicId) = 0;
		};
	}
}