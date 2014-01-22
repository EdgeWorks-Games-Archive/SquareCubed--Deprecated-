#pragma once

#include <CommonLib/postypes.h>

namespace Server {
	namespace Network {
		class IUnitSelectCallback {
		public: // Initialization/Uninitialization
			virtual ~IUnitSelectCallback() {}

		public: // Callback Functions
			virtual void ReceivedUnitOrder(unsigned int unitId, glm::vec2 pos) = 0;
		};
	}
}