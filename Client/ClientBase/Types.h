/** Contains foward declarations for types in this library.
 * If this file doesn't contain a type you need, and it's
 * within this library add it.
 */

#pragma once

namespace Core {
	class Engine;
}

namespace Graphics {
	class IGraphics;
	class ICamera;

	// Renderers
	class IUnitRenderer;
	class ITileRenderer;

	// Content Types
	class ITileArray;
}

namespace Input {
	class Input;
}

namespace Network {
	class INetwork;
	class IPacketHandler;

	// Handler Callbacks
	class IMainMenuCallback;
	class IUnitsCallback;
	class IPlayerCallback;
	class IWorldCallback;

	// Packet Dispatchers
	class IGameDispatcher;
	class IPlayerDispatcher;
#ifdef _DEBUG
	class IDebugDispatcher;
#endif
}

namespace Tools {
	namespace Player {
		class RPGPlayer;
	}
	namespace Units {
		class Units;
	}
}