#pragma once

#include "Types.h"

#include <CommonLib/unittypes.h>

#include <glm/glm.hpp>

namespace Physics { class DynamicRigidBody; }

namespace Server {
	namespace Units {
		/** Lowest level unit interface.
		 * Most likely you don't want to extend the interface.
		 * Instead extend DynamicUnit to get the physics functionality.
		 */
		class Unit {
			static unsigned int nextId;

		public:
			/** Unique Unit ID.
			 * Gets uniquely assigned on unit construction, used to identify the unit.
			 */
			const unsigned int ID;

		protected: // Initialization/Uninitialization
			Unit(const int health);
		public:
			virtual ~Unit();

		public: // Disallow Copy/Assign
			Unit& operator=(const Unit&) = delete;
			Unit(const Unit&) = delete;

		public: // Position/Rotation
			/** Returns the position of the unit.
			 * \return A reference to the position.
			 */
			virtual glm::vec2& GetPosition() = 0;
			/** Sets the position of the unit. */
			virtual void SetPosition(glm::vec2 position) = 0;

			/** Unit Rotation. */
			float Rotation;

		public: // Physics Sync
			/** TEMP FUNCTION!
			 * Temp function till fixed rigidbodies in units are supported by the network layer
			 */
			const virtual Physics::DynamicRigidBody& GetDynamicRigidBody() = 0;

		private: // Unit Data
			DataTypes::Health m_Health;

		public: // Unit Data Accessors
			/** Heals the unit for given amount of health.
			 * Heals the amount given or till max health is reached.
			 * Unit may ignore this if it does not keep track of health.
			 */
			void Heal(unsigned int health);

			/** Damages the unit for given amount of health.
			 * Unit may ignore this if it does not keep track of health.
			 */
			void Damage(unsigned int health);

			/** Returns the health of the unit.
			 * Using the reference to alter the unit's health results in
			 * undefined behavior. Instead use Heal and Damage for that.
			 * \return A constant reference to the unit's health.
			 */
			const DataTypes::Health& GetHealth();

			unsigned int GraphicId;

		public: // Tasks
			virtual void SetTask(std::unique_ptr<AI::ITask> task) = 0;

		public: // Game Loop
			virtual void Update(const float delta) = 0;
		};
	}
}