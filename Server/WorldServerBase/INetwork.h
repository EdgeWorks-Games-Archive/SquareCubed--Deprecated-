#pragma once

namespace Server {
	namespace Network {
		class INetworkFactory;
		class IPacketHandler;

		/// <summary>
		/// Implementations of INetwork are responsible for managing all network-related functionality
		/// including providing a factory class for packet handlers and dispatchers.
		/// </summary>
		class INetwork {
		public: // Initialization/Uninitialization
			virtual ~INetwork() {}

		public: // Packet Handler/Dispatcher Utility Functions
			/// <summary>
			/// Gets the <see cref="Network::INetworkFactory">INetworkFactory</see> for this instance.
			/// </summary>
			/// <returns>Returns the network factory.</returns>
			virtual INetworkFactory& GetFactory() = 0;

			/// <summary>
			/// Attaches the specified packet handler to this instance.
			/// Packet handlers once attached will participate in packet handling.
			/// <seealso cref="INetwork::Detach" />
			/// </summary>
			/// <param name="packetHandler">The packet handler that will be attached.</param>
			virtual void Attach(IPacketHandler& packetHandler) = 0;

			/// <summary>
			/// Detaches the specified packet handler from this instance.
			/// Packet handlers once detached will not participate in packet handling anymore.
			/// <seealso cref="INetwork::Attach" />
			/// </summary>
			/// <param name="packetHandler">The packet handler that will be detached.</param>
			virtual void Detach(IPacketHandler& packetHandler) = 0;

		public: // Network Error Reporting Functions

		public: // Game Loop
			/// <summary>Receives and handles all available packets.</summary>
			virtual void HandlePackets() = 0;
		};
	}
}