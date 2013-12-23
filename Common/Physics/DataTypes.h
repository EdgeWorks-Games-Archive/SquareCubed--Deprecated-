#pragma once

#include <glm/glm.hpp>

#include <memory>

namespace Physics {
	struct MassData final {
	private:
		float m_Mass;
		float m_InverseMass;

	public:
		MassData(const float mass);

		/** Sets the mass.
		 * Stores the mass internally and precalculates the inverse mass.
		 * \param[in]	mass	The mass to be stored.
		 */
		void SetMass(const float mass);

		/** Gets the mass.
		 * \return		The internally stored mass.
		 */
		inline const float GetMass() const { return m_Mass; }

		/** Gets the precalculated inverse mass.
		 * Used in calculations to avoid expensive division.
		 * \return		The internally stored inverse mass.
		 */
		inline const float GetInverseMass() const { return m_InverseMass; }
	};

	struct MaterialData {
		/** Describes the density of the material. */
		float Density;
		/** Describes the restitution or 'bounciness' of the material. */
		float Restitution;
	};

	/** Defines an Axis Aligned Bounding Box's data.
	 * Provides helper functions for dealing with AABB data.
	 */
	struct AABBData {
		/** Bottom left of the AABB. */
		glm::vec2 Min;
		/** Top right of the AABB. */
		glm::vec2 Max;

	public: // Helper functions
		/** Calculates if this AABB intersects another AABB.
		 * \param[in]	data	AABB data to compare this AABB with.
		 * \return		True if intersects, false otherwise.
		 */
		bool Intersects(const AABBData &data) const;

		/** Calculates if this AABB contains a point.
		 * \param[in]	point	Point to compare this AABB with.
		 * \return		True if contains, false otherwise.
		 */
		bool Contains(const glm::vec2 &point) const;
	};
}