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
		class IUnitSelectCallback;
#ifdef _DEBUG
		class IDebugCallback;
#endif

		// Packet Dispatchers
		class IUnitsDispatcher;
		class IPlayerDispatcher;
		class IWorldDispatcher;
	}

	namespace Units {
		class Unit;
		class AIUnit;

		namespace AI {
			class MoveBehavior;
		}
	}
}