#pragma once

namespace Server {
	namespace Network {
		class IPacketHandler;

		// Handler Callbacks
		class IAgentsCallback;
		class IPlayerCallback;

		// Packet Dispatchers
		class IAgentsDispatcher;
		class IPlayerDispatcher;
		class IWorldDispatcher;

		class INetworkFactory {
		public: // Initialization/Uninitialization
			virtual ~INetworkFactory() {}

		public: // Packet Handlers
			/// <summary>Creates a new IPacketHandler.</summary>
			/// <returns>Returns a pointer to a new IPacketHandler created in this function.</returns>
			virtual IPacketHandler* CreatePlayerHandler(IPlayerCallback &callback) = 0;

		public: // Packet Dispatchers
			/// <summary>Creates a new IGameDispatcher.</summary>
			/// <returns>Returns a pointer to a new IGameDispatcher created in this function.</returns>
			virtual IAgentsDispatcher* CreateAgentsDispatcher() = 0;

			/// <summary>Creates a new IPlayerDispatcher.</summary>
			/// <returns>Returns a pointer to a new IPlayerDispaycher created in this function.</returns>
			virtual IPlayerDispatcher* CreatePlayerDispatcher() = 0;

			/// <summary>Creates a new IWorldDispatcher.</summary>
			/// <returns>Returns a pointer to a new IWorldDispatcher created in this function.</returns>
			virtual IWorldDispatcher* CreateWorldDispatcher() = 0;
		};
	}
}