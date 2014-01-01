#include "BaseUnitTypes.h"

#include <CommonLib/PhysicsPacketDataTypes.h>

namespace Server {
	namespace Units {
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
	}
}