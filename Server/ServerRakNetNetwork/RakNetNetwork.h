#pragma once

#include "RakNetNetworkFactory.h"

#include <WorldServerBase/INetwork.h>

#include <CommonLib/Logger.h>

#include <RakNetTypes.h>

#include <memory>
#include <list>

namespace Server {
	namespace RakNetNetwork {
		class IRakNetPacketHandler;

		class RakNetNetwork final : public Network::INetwork {
			Utils::Logger m_Logger;
			RakNet::RakPeerInterface *m_Peer;

			// Packet Handlers
			RakNetNetworkFactory m_Factory;
			std::list<IRakNetPacketHandler*> m_PacketHandlers;

		public: // Initialization/Uninitialization
			RakNetNetwork(Utils::ILoggingManager &logManager, const int port, const int maxClients);
			~RakNetNetwork();

		public: // Misc Network Utility Functions
			RakNet::RakPeerInterface& GetRakPeer();

		public: // Packet Handler/Dispatcher Utility Functions
			Network::INetworkFactory& GetFactory();
			void Attach(Network::IPacketHandler& packetHandler);
			void Detach(Network::IPacketHandler& packetHandler);

		public: // Network Error Reporting Functions
			void ReportProtocolError();

		public: // Game Loop
			void HandlePackets();
		};
	}
}