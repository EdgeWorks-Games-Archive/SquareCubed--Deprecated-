#pragma once

#include <CommonLib/agenttypes.h>

#include <glm/glm.hpp>

namespace Physics { class DynamicRigidBody; }

namespace Server {
	namespace Agents {
		/** Lowest level agent interface.
		 * Most likely you don't want to extend the interface.
		 * Instead extend DynamicAgent to get the physics functionality.
		 */
		class IAgent {
			static unsigned int nextId;

		public:
			/** Unique Agent ID.
			 * Gets uniquely assigned on agent construction, used to identify the agent.
			 */
			const int ID;

			IAgent();
			virtual ~IAgent() {}

		public: // Position/Rotation
			/** Returns the position of the agent.
			 * \return A reference to the position.
			 */
			virtual glm::vec2& GetPosition() = 0;
			/** Sets the position of the agent. */
			virtual void SetPosition(glm::vec2 position) = 0;

			/** Agent Rotation. */
			float Rotation;

		public: // Physics Sync
			/** TEMP FUNCTION!
			 * Temp function till fixed rigidbodies in agents are supported by the network layer
			 */
			const virtual Physics::DynamicRigidBody& GetDynamicRigidBody() = 0;

		public: // Agent Data
			/** Heals the agent for given amount of health.
			 * Heals the amount given or till max health is reached.
			 * Agent may ignore this if it does not keep track of health.
			 */
			virtual void Heal(unsigned int health) = 0;

			/** Damages the agent for given amount of health.
			 * Agent may ignore this if it does not keep track of health.
			 */
			virtual void Damage(unsigned int health) = 0;

			/** Returns the health of the agent.
			 * Using the reference to alter the agent's health results in
			 * undefined behavior. Instead use Heal and Damage for that.
			 * \return A constant reference to the agent's health.
			 */
			virtual const DataTypes::Health& GetHealth() = 0;

			unsigned int GraphicId;

		public: // Game Loop
			virtual void Update(const float delta) = 0;
		};
	}
}