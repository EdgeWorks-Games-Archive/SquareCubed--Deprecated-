#pragma once

#include "Types.h"

#include <memory>

namespace Network {
	class INetworkFactory {
	public: // Initialization/Uninitialization
		virtual ~INetworkFactory() {}

	public: // Packet Handlers
		/// <summary>Creates a new IPacketHandler.</summary>
		/// <returns>Returns a pointer to a new IPacketHandler created in this function.</returns>
		virtual IPacketHandler* CreateMainMenuHandler(IMainMenuCallback &callback) = 0;

		/// <summary>Creates a new IPacketHandler.</summary>
		/// <returns>Returns a pointer to a new IPacketHandler created in this function.</returns>
		virtual IPacketHandler* CreateUnitsHandler(IUnitsCallback &callback) = 0;

		/// <summary>Creates a new IPacketHandler.</summary>
		/// <returns>Returns a pointer to a new IPacketHandler created in this function.</returns>
		virtual IPacketHandler* CreatePlayerHandler(IPlayerCallback &callback) = 0;

		/// <summary>Creates a new IPacketHandler.</summary>
		/// <returns>Returns a pointer to a new IPacketHandler created in this function.</returns>
		virtual IPacketHandler* CreateWorldHandler(IWorldCallback &callback) = 0;

	public: // Packet Dispatchers
		/** Creates a new IGameDispatcher.
		 * \return A pointer to a new IGameDispatcher created in this function.
		 */
		virtual IGameDispatcher* CreateGameDispatcher() = 0;

		/** Creates a new IPlayerDispatcher.
		 * \return A pointer to a new IPlayerDispatcher created in this function.
		 */
		virtual IPlayerDispatcher* CreatePlayerDispatcher() = 0;

		/** Creates a new IUnitSelectDispatcher.
		 * \return A pointer to a new IPlayerDispatcher created in this function.
		 */
		virtual IUnitSelectDispatcher* CreateUnitSelectDispatcher() = 0;

#ifdef _DEBUG
		/** Creates a new IDebugDispatcher.
		 * \return A pointer to a new IDebugDispatcher created in this function.
		 */
		virtual std::unique_ptr<IDebugDispatcher> CreateDebugDispatcher() = 0;
#endif
	};
}