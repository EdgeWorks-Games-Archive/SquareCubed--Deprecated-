#pragma once

#include <CommonLib/agenttypes.h>

namespace Network {
	class IPlayerCallback {
	public: // Initialization/Uninitialization
		virtual ~IPlayerCallback() {}

	public: // Callback Functions
		virtual void ReceivedPlayerDesc(unsigned int agentId, DataTypes::Health health) = 0;
	};
}