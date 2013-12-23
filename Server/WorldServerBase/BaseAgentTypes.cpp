#include "BaseAgentTypes.h"

#include <CommonLib/PhysicsPacketDataTypes.h>

#include <algorithm>

namespace Server {
	namespace Agents {
		// Basic Getters and Setters

		glm::vec2& DynamicAgent::GetPosition() { return m_RigidBody.Position; }
		void DynamicAgent::SetPosition(glm::vec2 position) { m_RigidBody.Position = std::move(position); }

		// Physics Sync

		void DynamicAgent::ReceivedPhysicsUpdate(const CNetwork::PhysicsUpdateData &physicsData) {
			m_RigidBody.Position = std::move(physicsData.Position);
			m_RigidBody.Force = std::move(physicsData.Force);
			m_RigidBody.Velocity = std::move(physicsData.Velocity);
			Rotation = std::move(physicsData.Rotation);
		}

		const Physics::DynamicRigidBody& DynamicAgent::GetDynamicRigidBody() { return m_RigidBody; }

		// Agent Data

		void DynamicAgent::Heal(unsigned int health) {
			m_Health.Current = std::min(m_Health.Max, m_Health.Current + health);
		}

		void DynamicAgent::Damage(unsigned int health) {
			m_Health.Current = std::max(0, static_cast<int>(m_Health.Current) - static_cast<int>(health));
		}

		const DataTypes::Health& DynamicAgent::GetHealth() { return m_Health;}
	}
}