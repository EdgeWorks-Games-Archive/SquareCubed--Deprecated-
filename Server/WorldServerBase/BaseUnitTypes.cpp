#include "BaseUnitTypes.h"

#include <CommonLib/PhysicsPacketDataTypes.h>

#include <algorithm>

namespace Server {
	namespace Units {
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

		// Unit Data

		void DynamicUnit::Heal(unsigned int health) {
			m_Health.Current = std::min(m_Health.Max, m_Health.Current + health);
		}

		void DynamicUnit::Damage(unsigned int health) {
			m_Health.Current = std::max(0, static_cast<int>(m_Health.Current) - static_cast<int>(health));
		}

		const DataTypes::Health& DynamicUnit::GetHealth() { return m_Health;}
	}
}