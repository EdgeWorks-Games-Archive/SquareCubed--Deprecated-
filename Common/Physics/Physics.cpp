#include "Physics.h"

#include "IBroadphase.h"
#include "DynamicRigidBody.h"

#include <CommonLib/LoggingManager.h>

namespace Physics {
	Physics::Physics(Utils::ILoggingManager &logManager, std::unique_ptr<IBroadphase> broadphase) :
		m_Logger(logManager.CreateLogger("Physics")),

		m_Broadphase(std::move(broadphase)),

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

	// Accessors

	const std::list<std::reference_wrapper<DynamicRigidBody>>& Physics::GetAllDynamic() { return m_DynamicRigidBodies; }
	IBroadphase& Physics::GetBroadphase() { return *m_Broadphase; }

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
		// Update all velocities and collisions
		for (DynamicRigidBody &rigidBody : m_DynamicRigidBodies) {
			rigidBody.UpdateVelocity(delta, *this);
		}

		// Update all positions, UpdateVelocity and UpdateCollisions
		// rely on this position so only now change it
		for (DynamicRigidBody &rigidBody : m_DynamicRigidBodies) {
			rigidBody.UpdatePosition(delta);
		}
	}
}