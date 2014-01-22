#pragma once

#include <CommonLib/unittypes.h>

namespace Network {
	class IPlayerCallback {
	public: // Initialization/Uninitialization
		virtual ~IPlayerCallback() {}

	public: // Callback Functions
		virtual void ReceivedPlayerDesc(unsigned int unitId, DataTypes::Health health) = 0;
	};
}