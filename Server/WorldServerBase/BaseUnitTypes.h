#pragma once

#include "IUnit.h"

#include <Physics/Physics.h>
#include <Physics/DynamicRigidBody.h>
#include <Physics/CircleCollider.h>

namespace CNetwork { struct PhysicsUpdateData; }

namespace Server {
	namespace Units {
		/// <summary>Base type for creating basic units.</summary>
		class DynamicUnit : public IUnit {
			DataTypes::Health m_Health;

		protected:
			Physics::Physics &m_Physics;
			Physics::DynamicRigidBody m_RigidBody;

		public: // Initialization/Uninitialization
			DynamicUnit(Physics::Physics &physics, const int health) :
				IUnit(),
				m_Health(health, health),
				m_Physics(physics),
				m_RigidBody(std::make_unique<Physics::CircleCollider>(0.3f), 2.0f)
			{
				m_Physics.AttachDynamic(m_RigidBody);
			}

			virtual ~DynamicUnit() {
				m_Physics.DetachDynamic(m_RigidBody);
			}

		public: // Basic Getters and Setters
			glm::vec2& GetPosition();
			void SetPosition(glm::vec2 position);

		public: // Physics Sync
			void ReceivedPhysicsUpdate(const CNetwork::PhysicsUpdateData &physicsData);
			const Physics::DynamicRigidBody& GetDynamicRigidBody();

		public: // Unit Data
			void Heal(unsigned int health);
			void Damage(unsigned int health);
			const DataTypes::Health& GetHealth();
		};

		class DummyUnit final : public DynamicUnit {
		public: // Initialization/Uninitialization
			DummyUnit(Physics::Physics &physics, const int health) :
				DynamicUnit(physics, health)
			{}

		public: // Game Loop
			virtual void Update(const float delta) {}
		};

		class NPCUnit final : public DynamicUnit {
		public: // Initialization/Uninitialization
			NPCUnit(Physics::Physics &physics, const int health) :
				DynamicUnit(physics, health)
			{}

		public: // Game Loop
			virtual void Update(const float delta) {}
		};
	}
}