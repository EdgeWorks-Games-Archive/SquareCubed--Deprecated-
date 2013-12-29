#pragma once

#include <CommonLib/postypes.h>
#include <CommonLib/unittypes.h>
#include <Physics/Physics.h>
#include <Physics/DynamicRigidBody.h>
#include <Physics/CircleCollider.h>

#include <glm/glm.hpp>

namespace CNetwork { struct PhysicsUpdateData; }

namespace Tools {
	namespace Units {
		typedef unsigned int UnitID;

		class IUnit {
		public:
			const UnitID ID;

			Anglef Rotation;

			DataTypes::Health Health;
			unsigned int GraphicID;

		public:
			IUnit(UnitID id, DataTypes::Health health) :
				ID(id),
				Rotation(),

				Health(std::move(health)),
				GraphicID()
			{}
			virtual ~IUnit() {}

		public:
			/// <summary>
			/// Sets the position of this Unit object.
			/// This function is used to make sure the player unit doesn't get
			/// affected by unit position packets and to smooth unit movement.
			/// </summary>
			/// <param name="data">The received physics data.</param>
			virtual void ReceivedUpdatePhysics(const CNetwork::PhysicsUpdateData &data) = 0;

			virtual glm::vec2& GetPosition() = 0;
			virtual Anglef& GetRotation() = 0;
		};

		class DynamicUnit : public IUnit {
			Physics::Physics &m_Physics;

		public:
			Physics::DynamicRigidBody RigidBody;

		public:
			DynamicUnit(UnitID id, DataTypes::Health health, Physics::Physics &physics) :
				m_Physics(physics),
				IUnit(id, std::move(health)),
				RigidBody(std::make_unique<Physics::CircleCollider>(0.25f), 2.0f)
			{
				m_Physics.AttachDynamic(RigidBody);
			}
			virtual ~DynamicUnit() {
				m_Physics.DetachDynamic(RigidBody);
			}

		public:
			virtual void ReceivedUpdatePhysics(const CNetwork::PhysicsUpdateData &data);
			virtual glm::vec2& GetPosition() { return RigidBody.Position; }
			virtual Anglef& GetRotation() { return Rotation; }
		};
	}
}