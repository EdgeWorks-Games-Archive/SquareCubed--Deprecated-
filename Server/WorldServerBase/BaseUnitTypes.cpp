#include "BaseUnitTypes.h"

#include "ITask.h"

#include <CommonLib/PhysicsPacketDataTypes.h>

namespace Server {
	namespace Units {
		/// Dynamic Unit ///

		// Initialization/Uninitialization

		DynamicUnit::DynamicUnit(Physics::Physics &physics, const int health) :
			Unit(health),
			m_Physics(physics),
			m_RigidBody(std::make_unique<Physics::CircleCollider>(0.3f), 2.0f)
		{
			m_Physics.AttachDynamic(m_RigidBody);
		}

		DynamicUnit::~DynamicUnit() {
			m_Physics.DetachDynamic(m_RigidBody);
		}

		// Basic Getters and Setters

		glm::vec2& DynamicUnit::GetPosition() { return m_RigidBody.Position; }
		void DynamicUnit::SetPosition(glm::vec2 position) { m_RigidBody.Position = std::move(position); }

		// Physics Sync

		void DynamicUnit::ReceivedPhysicsUpdate(const CNetwork::PhysicsUpdateData &physicsData) {
			m_RigidBody.Position = std::move(physicsData.Position);
			m_RigidBody.Force = std::move(physicsData.Force);
			m_RigidBody.Velocity = std::move(physicsData.Velocity);
			Rotation = std::move(physicsData.Rotation);
		}

		const Physics::DynamicRigidBody& DynamicUnit::GetDynamicRigidBody() { return m_RigidBody; }

		/// DummyUnit ///

		// Initialization/Uninitialization

		DummyUnit::DummyUnit(Physics::Physics &physics, const int health) :
			DynamicUnit(physics, health)
		{}

		// Tasks

		void DummyUnit::SetTask(std::unique_ptr<AI::ITask> task) {
		}

		// Game Loop

		void DummyUnit::Update(const float) {}

		/// NPCUnit ///

		// Initialization/Uninitialization

		NPCUnit::NPCUnit(Physics::Physics &physics, const int health) :
			DynamicUnit(physics, health)
		{}

		// Tasks

		void NPCUnit::SetTask(std::unique_ptr<AI::ITask> task) {
		}

		// Game Loop

		void NPCUnit::Update(const float) {
		}
	}
}