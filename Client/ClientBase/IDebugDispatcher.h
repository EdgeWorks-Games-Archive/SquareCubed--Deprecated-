#pragma once

#ifdef _DEBUG

#include <glm/glm.hpp>

namespace Network {
	class IDebugDispatcher {
	public: // Initialization/Uninitialization
		virtual ~IDebugDispatcher() {}

	public: // Send Functions
		virtual void SpawnUnit(const glm::vec2 &pos) = 0;
	};
}

#endif