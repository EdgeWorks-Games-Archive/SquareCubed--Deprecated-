#pragma once

namespace Server {
	namespace Network {
		class IPacketHandler {
		public: // Initialization/Uninitialization
			virtual ~IPacketHandler() {}

			// How packets are transported from the Network object to the
			// packet handlers is the responsibility of the implementation,
			// not of the interface.
			// Of course a common class to extend is still needed to restrict
			// registering of packet handlers to the correct classes.
		};
	}
}