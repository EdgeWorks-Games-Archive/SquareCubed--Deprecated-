#pragma once

#include <glm/glm.hpp>
#include "Types.h"

namespace Network {
	class IUnitSelectDispatcher {
	public: // Initialization/Uninitialization
		virtual ~IUnitSelectDispatcher() {}

	public: // Send Functions
		virtual void SendMoveOrder(Tools::Units::UnitID id, const glm::vec2 &pos) = 0;
	};
}