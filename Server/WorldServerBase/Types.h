/** Contains foward declarations for types in this library.
* If this file doesn't contain a type you need, and it's
* within this library add it.
*/

#pragma once

namespace Server {
	namespace Network {
		class INetwork;
		class IPacketHandler;

		// Handler Callbacks
		class IPlayerCallback;
		class IDebugCallback;

		// Packet Dispatchers
		class IUnitsDispatcher;
		class IPlayerDispatcher;
		class IWorldDispatcher;
	}
}