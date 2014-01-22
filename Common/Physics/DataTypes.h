#pragma once

#include <glm/glm.hpp>

#include <memory>

namespace Physics {
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