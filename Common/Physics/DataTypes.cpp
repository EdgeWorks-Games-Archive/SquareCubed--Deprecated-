#include "DataTypes.h"

namespace Physics {
	/// MassData ///

	MassData::MassData(const float mass) :
		m_Mass(std::move(mass)),
		m_InverseMass(1 / m_Mass)
	{}

	void MassData::SetMass(const float mass) {
		m_Mass = std::move(mass);
		m_InverseMass = 1 / m_Mass;
	}

	/// AABBData ///

	bool AABBData::Intersects(const AABBData& data) const {
		if (Max.x < data.Min.x || Min.x > data.Max.x) return false;
		if (Max.y < data.Min.y || Min.y > data.Max.y) return false;

		// No separating axis found, therefor there is at least one overlapping axis
		return true;
	}

	bool AABBData::Contains(const glm::vec2 &point) const {
		if (Max.x < point.x || Min.x > point.x) return false;
		if (Max.y < point.y || Min.y > point.y) return false;

		// No out of bounds found, therefor it's within the bounding box
		return true;
	}
}