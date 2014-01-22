#pragma once

#include "RakNetNetworkFactory.h"

#include <ClientBase/INetwork.h>

#include <CommonLib/Logger.h>

#include <RakNetTypes.h>

#include <memory>
#include <list>

namespace RakNetNetwork {
	class IRakNetPacketHandler;

	class RakNetNetwork final : public Network::INetwork {
		Utils::Logger m_Logger;
		RakNet::RakPeerInterface *m_Peer;
		
		// Server GUIDs
		RakNet::RakNetGUID m_WorldServerGUID;

		// Packet Handlers
		RakNetNetworkFactory m_Factory;
		std::list<IRakNetPacketHandler*> m_PacketHandlers;

	public: // Initialization/Uninitialization
		RakNetNetwork(Utils::ILoggingManager &logManager);
		~RakNetNetwork();

	public: // Misc Network Utility Functions
		bool Connect(const char* host, const int port);
		void Disconnect();
		RakNet::RakPeerInterface& GetRakPeer();
		RakNet::RakNetGUID& GetWorldServer();

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