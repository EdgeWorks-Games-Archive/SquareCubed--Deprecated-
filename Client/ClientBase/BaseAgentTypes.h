#pragma once

#include <CommonLib/postypes.h>
#include <CommonLib/agenttypes.h>
#include <Physics/Physics.h>
#include <Physics/DynamicRigidBody.h>
#include <Physics/CircleCollider.h>

#include <glm/glm.hpp>

namespace CNetwork { struct PhysicsUpdateData; }

namespace Tools {
	namespace Agents {
		typedef unsigned int AgentID;

		class IAgent {
		public:
			const AgentID ID;

			Anglef Rotation;

			DataTypes::Health Health;
			unsigned int GraphicID;

		public:
			IAgent(AgentID id, DataTypes::Health health) :
				ID(id),
				Rotation(),

				Health(std::move(health)),
				GraphicID()
			{}
			virtual ~IAgent() {}

		public:
			/// <summary>
			/// Sets the position of this Agent object.
			/// This function is used to make sure the player agent doesn't get
			/// affected by agent position packets and to smooth agent movement.
			/// </summary>
			/// <param name="data">The received physics data.</param>
			virtual void ReceivedUpdatePhysics(const CNetwork::PhysicsUpdateData &data) = 0;

			virtual glm::vec2& GetPosition() = 0;
			virtual Anglef& GetRotation() = 0;
		};

		class PhysicsAgent : public IAgent {
			Physics::Physics &m_Physics;

		public:
			Physics::DynamicRigidBody RigidBody;

		public:
			PhysicsAgent(AgentID id, DataTypes::Health health, Physics::Physics &physics) :
				m_Physics(physics),
				IAgent(id, std::move(health)),
				RigidBody(std::make_unique<Physics::CircleCollider>(0.25f), 2.0f)
			{
				m_Physics.AttachDynamic(RigidBody);
			}
			virtual ~PhysicsAgent() {
				m_Physics.DetachDynamic(RigidBody);
			}

		public:
			virtual void ReceivedUpdatePhysics(const CNetwork::PhysicsUpdateData &data);
			virtual glm::vec2& GetPosition() { return RigidBody.Position; }
			virtual Anglef& GetRotation() { return Rotation; }
		};
	}
}