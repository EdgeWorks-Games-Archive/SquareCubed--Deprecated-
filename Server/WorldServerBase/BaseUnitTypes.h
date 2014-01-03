#pragma once

#include "Unit.h"

#include <Physics/Physics.h>
#include <Physics/DynamicRigidBody.h>
#include <Physics/CircleCollider.h>

namespace CNetwork { struct PhysicsUpdateData; }

namespace Server {
	namespace Units {
		/** Base type for creating basic units. */
		class DynamicUnit : public Unit {
		protected:
			Physics::Physics &m_Physics;
			Physics::DynamicRigidBody m_RigidBody;

		public: // Initialization/Uninitialization
			DynamicUnit(Physics::Physics &physics, const int health);
			virtual ~DynamicUnit();

		public: // Basic Getters and Setters
			glm::vec2& GetPosition();
			void SetPosition(glm::vec2 position);

		public: // Physics Sync
			void ReceivedPhysicsUpdate(const CNetwork::PhysicsUpdateData &physicsData);
			const Physics::DynamicRigidBody& GetDynamicRigidBody();
		};

		class DummyUnit final : public DynamicUnit {
		public: // Initialization/Uninitialization
			DummyUnit(Physics::Physics &physics, const int health);

		public: // Tasks
			void SetTask(std::unique_ptr<AI::ITask> task);

		public: // Game Loop
			void Update(const float delta);
		};

		class NPCUnit final : public DynamicUnit {
		public: // Initialization/Uninitialization
			NPCUnit(Physics::Physics &physics, const int health);

		public: // Tasks
			void SetTask(std::unique_ptr<AI::ITask> task);

		public: // Game Loop
			void Update(const float delta);
		};
	}
}