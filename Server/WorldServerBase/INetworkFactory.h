#pragma once

#include "Types.h"

#include <memory>

namespace Server {
	namespace Network {
		class INetworkFactory {
		public: // Initialization/Uninitialization
			virtual ~INetworkFactory() {}

		public: // Packet Handlers
			/// <summary>Creates a new IPacketHandler.</summary>
			/// <returns>Returns a pointer to a new IPacketHandler created in this function.</returns>
			virtual IPacketHandler* CreatePlayerHandler(IPlayerCallback &callback) = 0;

#ifdef _DEBUG
			/** Creates a new IPacketHandler.
			 * \return A pointer to a new IPacketHandler created in this function.
			 */
			virtual std::unique_ptr<IPacketHandler> CreateDebugHandler(IDebugCallback &callback) = 0;
#endif

		public: // Packet Dispatchers
			/// <summary>Creates a new IGameDispatcher.</summary>
			/// <returns>Returns a pointer to a new IGameDispatcher created in this function.</returns>
			virtual IUnitsDispatcher* CreateUnitsDispatcher() = 0;

			/// <summary>Creates a new IPlayerDispatcher.</summary>
			/// <returns>Returns a pointer to a new IPlayerDispaycher created in this function.</returns>
			virtual IPlayerDispatcher* CreatePlayerDispatcher() = 0;

			/// <summary>Creates a new IWorldDispatcher.</summary>
			/// <returns>Returns a pointer to a new IWorldDispatcher created in this function.</returns>
			virtual IWorldDispatcher* CreateWorldDispatcher() = 0;
		};
	}
}