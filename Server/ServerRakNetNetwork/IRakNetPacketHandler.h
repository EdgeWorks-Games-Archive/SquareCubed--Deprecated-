#pragma once

#include <WorldServerBase/IPacketHandler.h>

namespace RakNet { struct Packet; }

namespace Server {
	namespace RakNetNetwork {
		class IRakNetPacketHandler : public Network::IPacketHandler {
		public: // Initialization/Uninitialization
			virtual ~IRakNetPacketHandler() {}

		public: // Game Loop
			virtual bool HandlePacket(RakNet::Packet &packet) = 0;
		};
	}
}