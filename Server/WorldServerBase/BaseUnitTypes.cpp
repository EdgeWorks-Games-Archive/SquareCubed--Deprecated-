#include "BaseUnitTypes.h"

#include <CommonLib/PhysicsPacketDataTypes.h>

namespace Server {
	namespace Units {
		/// Dynamic Unit ///

		// Initialization/Uninitialization

		DynamicUnit::DynamicUnit(Physics::Physics &physics, const int health) :
			Unit(health),
			m_Physics(physics),
			RigidBody(m_Physics, std::make_unique<Physics::CircleCollider>(0.3f), 10.0f)
		{
		}

		DynamicUnit::~DynamicUnit() {}

		// Basic Getters and Setters

		glm::vec2& DynamicUnit::GetPosition() { return RigidBody.Position; }
		void DynamicUnit::SetPosition(glm::vec2 position) { RigidBody.Position = std::move(position); }

		// Physics Sync

		void DynamicUnit::ReceivedPhysicsUpdate(const CNetwork::PhysicsUpdateData &physicsData) {
			RigidBody.Position = physicsData.Position;
			Rotation = physicsData.Rotation;
			RigidBody.Velocity = physicsData.Velocity;
			RigidBody.TargetVelocity = physicsData.TargetVelocity;
		}

		const Physics::DynamicRigidBody& DynamicUnit::GetDynamicRigidBody() { return RigidBody; }

		/// DummyUnit ///

		// Initialization/Uninitialization

		DummyUnit::DummyUnit(Physics::Physics &physics, const int health) :
			DynamicUnit(physics, health)
		{}

		// Game Loop

		void DummyUnit::Update(const float) {}

		/// NPCUnit ///

		// Initialization/Uninitialization

		AIUnit::AIUnit(Physics::Physics &physics, const int health) :
			DynamicUnit(physics, health),
			MoveBehavior(2.0f)
		{}

		AIUnit::~AIUnit() {}

		// Game Loop

		void AIUnit::Update(const float delta) {
			MoveBehavior.Update(delta, *this);
		}
	}
}