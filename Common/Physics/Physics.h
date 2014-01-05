#pragma once

#include <CommonLib/Logger.h>

#include <memory>
#include <list>

/** Contains all functionality related to the Physics module.
 */
namespace Physics {
	class IBroadphase;

	//class FixedRigidBody;
	class DynamicRigidBody;

	class Physics final {
		Utils::Logger m_Logger;

		std::unique_ptr<IBroadphase> m_Broadphase;

		std::list<std::reference_wrapper<DynamicRigidBody>> m_DynamicRigidBodies;

	public: // Initialization/Uninitialization
		Physics(Utils::ILoggingManager &logManager, std::unique_ptr<IBroadphase> broadphase);
		~Physics();

	public: // Accessors
		const std::list<std::reference_wrapper<DynamicRigidBody>>& GetAllDynamic();
		IBroadphase& GetBroadphase();

	public: // Attach/Detach Rigidbodies
		/** Attaches a dynamic rigidbody to the physics engine.
		 * This will update the rigidbody when the physics state is updated.
		 * \param[in, out]	rigidBody	A reference to the rigidbody.
		 */
		void AttachDynamic(DynamicRigidBody &rigidBody);

		/** Detatched a dynamic rigidbody from the physics engine.
		 * \param[in]	rigidBody	A reference to the rigidbody.
		 */
		void DetachDynamic(DynamicRigidBody &rigidBody);

	public: // Game Loop
		/** Updates the physics state.
		 * \param[in]	delta	The delta time to update the physics with.
		 */
		void UpdatePhysics(const float delta);
	};
}