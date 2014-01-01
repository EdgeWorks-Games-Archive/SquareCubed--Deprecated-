#include "Unit.h"

#include <algorithm>

namespace Server {
	namespace Units {
		unsigned int Unit::nextId = 0;

		Unit::Unit(const int health) :
			ID(nextId),
			Rotation(),

			m_Health(health, health),
			GraphicId()
		{
			nextId++;
		}

		Unit::~Unit() {}

		// Unit Data

		void Unit::Heal(unsigned int health) {
			m_Health.Current = std::min(m_Health.Max, m_Health.Current + health);
		}

		void Unit::Damage(unsigned int health) {
			m_Health.Current = std::max(0, static_cast<int>(m_Health.Current) - static_cast<int>(health));
		}

		const DataTypes::Health& Unit::GetHealth() { return m_Health; }
	}
}