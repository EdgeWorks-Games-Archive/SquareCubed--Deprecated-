#pragma once

#include <CommonLib/worldtypes.h>

namespace Network {
	class IWorldCallback {
	public: // Initialization/Uninitialization
		virtual ~IWorldCallback() {}

	public: // Callback Functions
		virtual void ReceivedWorldChunk(DataTypes::Chunk chunk) = 0;
	};
}