#include "BaseUnitTypes.h"

#include "ITask.h"
#include "StandAtTask.h"

#include <CommonLib/PhysicsPacketDataTypes.h>

namespace Server {
	namespace Units {
		/// Dynamic Unit ///

		// Initialization/Uninitialization

		DynamicUnit::DynamicUnit(Physics::Physics &physics, const int health) :
			Unit(health),
			m_Physics(physics),
			RigidBody(std::make_unique<Physics::CircleCollider>(0.3f), 2.0f)
		{
			m_Physics.AttachDynamic(RigidBody);
		}

		DynamicUnit::~DynamicUnit() {
			m_Physics.DetachDynamic(RigidBody);
		}

		// Basic Getters and Setters

		glm::vec2& DynamicUnit::GetPosition() { return RigidBody.Position; }
		void DynamicUnit::SetPosition(glm::vec2 position) { RigidBody.Position = std::move(position); }

		// Physics Sync

		void DynamicUnit::ReceivedPhysicsUpdate(const CNetwork::PhysicsUpdateData &physicsData) {
			RigidBody.Position = std::move(physicsData.Position);
			RigidBody.Force = std::move(physicsData.Force);
			RigidBody.Velocity = std::move(physicsData.Velocity);
			Rotation = std::move(physicsData.Rotation);
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
			m_ActiveTask(std::make_unique<AI::StandAtTask>(glm::vec2(0, 0)))
		{}

		AIUnit::~AIUnit() {}

		// Tasks

		void AIUnit::SetTask(std::unique_ptr<AI::ITask> task) {
			m_ActiveTask = std::move(task);
		}

		// Game Loop

		void AIUnit::Update(const float delta) {
			if (m_ActiveTask != nullptr)
				m_ActiveTask->Update(delta, *this);
		}
	}
}