#pragma once

#include <memory>

namespace DataTypes {
	struct Health final {
		unsigned int Current;
		unsigned int Max;

		Health() : Health(1, 1) {}
		Health(const int health) : Health(health, health) {}
		Health(const int health, const int maxHealth) :
			Current(std::move(health)),
			Max(std::move(maxHealth))
		{}
	};
}