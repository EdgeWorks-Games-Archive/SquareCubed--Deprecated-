#pragma once

#include "DataTypes.h"
#include "ICollider.h"

#include <memory>

namespace Physics {
	class Physics;

	class IRigidBody {
	public: // Public Common Physics Data
		glm::vec2 Position;
		MaterialData Material;

	protected: // Protected Common Physics Data
		friend class Physics;
		std::unique_ptr<ICollider> pm_Collider;

	protected: // Internal Protected Wrappers
		void UpdateBroadphase();

	public:
		IRigidBody(std::unique_ptr<ICollider> collider) :
			Position(),
			Material(),
			pm_Collider(std::move(collider))
		{
			UpdateBroadphase();
		}
		virtual ~IRigidBody() {}

	protected: // Protected Physics Loop Functions
		friend class Physics;

		/// <summary>
		/// Updates the physics state of the IRigidBody with time delta.
		/// </summary>
		/// <param name="delta">The delta time.</param>
		virtual void UpdateVelocity(const float delta, Physics &physics) = 0;
		virtual void ResolveCollisions() = 0;

	public: // Public Broadphase Data
		AABBData BroadphaseAABB;
		float BroadphaseRadius;
	};

	/*class FixedRigidBody final : public IRigidBody {
		void UpdatePhysics(const float delta) {}
		void ResolveCollisions() {}
	};*/
}