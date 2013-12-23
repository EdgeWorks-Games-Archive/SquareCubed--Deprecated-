#pragma once

namespace Network {
	class IPacketHandler;

	// Handler Callbacks
	class IMainMenuCallback;
	class IAgentsCallback;
	class IPlayerCallback;
	class IWorldCallback;

	// Packet Dispatchers
	class IGameDispatcher;
	class IPlayerDispatcher;

	class INetworkFactory {
	public: // Initialization/Uninitialization
		virtual ~INetworkFactory() {}

	public: // Packet Handlers
		/// <summary>Creates a new IPacketHandler.</summary>
		/// <returns>Returns a pointer to a new IPacketHandler created in this function.</returns>
		virtual IPacketHandler* CreateMainMenuHandler(IMainMenuCallback &callback) = 0;

		/// <summary>Creates a new IPacketHandler.</summary>
		/// <returns>Returns a pointer to a new IPacketHandler created in this function.</returns>
		virtual IPacketHandler* CreateAgentsHandler(IAgentsCallback &callback) = 0;

		/// <summary>Creates a new IPacketHandler.</summary>
		/// <returns>Returns a pointer to a new IPacketHandler created in this function.</returns>
		virtual IPacketHandler* CreatePlayerHandler(IPlayerCallback &callback) = 0;

		/// <summary>Creates a new IPacketHandler.</summary>
		/// <returns>Returns a pointer to a new IPacketHandler created in this function.</returns>
		virtual IPacketHandler* CreateWorldHandler(IWorldCallback &callback) = 0;

	public: // Packet Dispatchers
		/// <summary>Creates a new IGameDispatcher.</summary>
		/// <returns>Returns a pointer to a new IGameDispatcher created in this function.</returns>
		virtual IGameDispatcher* CreateGameDispatcher() = 0;

		/// <summary>Creates a new IPlayerDispatcher.</summary>
		/// <returns>Returns a pointer to a new IPlayerDispaycher created in this function.</returns>
		virtual IPlayerDispatcher* CreatePlayerDispatcher() = 0;
	};
}