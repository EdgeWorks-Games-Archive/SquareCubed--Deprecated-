#pragma once

#include "IClientID.h"

#include <CommonLib/worldtypes.h>

namespace Server {
	namespace Network {
		class IWorldDispatcher {
		public: // Initialization/Uninitialization
			virtual ~IWorldDispatcher() {}

		public: // Send Functions
			virtual void SendWorldChunk(const IClientID &clientId, const DataTypes::Chunk &chunk) = 0;
		};
	}
}