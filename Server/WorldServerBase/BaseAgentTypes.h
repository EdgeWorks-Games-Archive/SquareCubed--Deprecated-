#pragma once

#include "IAgent.h"

#include <Physics/Physics.h>
#include <Physics/DynamicRigidBody.h>
#include <Physics/CircleCollider.h>

namespace CNetwork { struct PhysicsUpdateData; }

namespace Server {
	namespace Agents {
		/// <summary>Base type for creating basic agents.</summary>
		class DynamicAgent : public IAgent {
			DataTypes::Health m_Health;

		protected:
			Physics::Physics &m_Physics;
			Physics::DynamicRigidBody m_RigidBody;

		public:
			DynamicAgent(Physics::Physics &physics, const int health, const float mass) :
				IAgent(),
				m_Health(health, health),
				m_Physics(physics),
				m_RigidBody(std::make_unique<Physics::CircleCollider>(0.25f), mass)
			{
				m_Physics.AttachDynamic(m_RigidBody);
			}

			virtual ~DynamicAgent() {
				m_Physics.DetachDynamic(m_RigidBody);
			}

		public: // Basic Getters and Setters
			glm::vec2& GetPosition();
			void SetPosition(glm::vec2 position);

		public: // Physics Sync
			void ReceivedPhysicsUpdate(const CNetwork::PhysicsUpdateData &physicsData);
			const Physics::DynamicRigidBody& GetDynamicRigidBody();

		public: // Agent Data
			void Heal(unsigned int health);
			void Damage(unsigned int health);
			const DataTypes::Health& GetHealth();

		public: // Game Loop
			virtual void Update(const float delta) {}
		};
	}
}