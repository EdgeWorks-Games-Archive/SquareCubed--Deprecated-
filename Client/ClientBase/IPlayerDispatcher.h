#pragma once

#include <Physics/DynamicRigidBody.h>

namespace Network {
	class IPlayerDispatcher {
	public: // Initialization/Uninitialization
		virtual ~IPlayerDispatcher() {}

	public: // Send Functions
		virtual void SendPlayerPhysics(const Physics::DynamicRigidBody &rigidBody, const float rotation) = 0;
	};
}