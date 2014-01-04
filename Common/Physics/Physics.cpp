#include "Physics.h"

#include "IBroadphase.h"
#include "DynamicRigidBody.h"

#include <CommonLib/LoggingManager.h>

namespace Physics {
	Physics::Physics(Utils::ILoggingManager &logManager, std::unique_ptr<IBroadphase> broadphase) :
		m_Logger(logManager.CreateLogger("Physics")),

		m_Broadphase(std::move(broadphase)),
		m_CollisionResolver(),

		m_DynamicRigidBodies()
	{
		// Log Initialiation
		m_Logger.LogInfo("Physics Initialized");
	}

	Physics::~Physics() {
#ifdef _DEBUG
		for (DynamicRigidBody &rigidBody : m_DynamicRigidBodies) {
			m_Logger.LogWarning("RigidBody %p remained till destruction, possible memory leak!", &rigidBody);
		}
#endif
	}

	// Attach/Detach Rigidbodies

	void Physics::AttachDynamic(DynamicRigidBody &rigidBody) {
		m_DynamicRigidBodies.push_back(rigidBody);
	}

	void Physics::DetachDynamic(DynamicRigidBody &rigidBody) {
		auto it = m_DynamicRigidBodies.begin();
		while (it != m_DynamicRigidBodies.end()) {
			if (&(it->get()) == &rigidBody) {
				// Found it!
				it = m_DynamicRigidBodies.erase(it);
				return;
			}
			else
				++it;
		}
	}

	// Game Loop

	void Physics::UpdatePhysics(const float delta) {
		// Update all rigidbody positions
		for (DynamicRigidBody &rigidBody : m_DynamicRigidBodies) {
			rigidBody.UpdatePhysics(delta);
		}

		// Run Collision Detection
		m_Broadphase->DetectCollision(m_DynamicRigidBodies, m_CollisionResolver);
	}
}