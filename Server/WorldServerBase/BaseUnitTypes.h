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
			Physics::Physics &m_Physics;

		public:
			Physics::DynamicRigidBody RigidBody;

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

		public: // Game Loop
			void Update(const float delta);
		};

		class AIUnit final : public DynamicUnit {
			std::unique_ptr<AI::ITask> m_ActiveTask;

		public: // Initialization/Uninitialization
			AIUnit(Physics::Physics &physics, const int health);
			~AIUnit();
			
		public: // Tasks
			void SetTask(std::unique_ptr<AI::ITask> task);

		public: // Game Loop
			void Update(const float delta);
		};
	}
}