#include "RakNetNetwork.h"
#include "RakNetNetworkLoader.h"

#include "IRakNetPacketHandler.h"

#include <WorldServerBase/gdefines.h>

#include <CRakNetNetwork/PacketTypes.h>
#include <CommonLib/ILoggingManager.h>

#include <RakPeerInterface.h>
#include <BitStream.h>

namespace Server {
	namespace RakNetNetwork {
		// Factory to avoid including the big compiler-grinding-to-a-crawl file
		Network::INetwork* LoadNetwork(Utils::ILoggingManager &logManager, const int port, const int maxClients) { return new RakNetNetwork(logManager, port, maxClients); }

		// Initialization/Uninitialization

		RakNetNetwork::RakNetNetwork(Utils::ILoggingManager &logManager, const int port, const int maxClients) :
			m_Logger(logManager.CreateLogger("Network")),
			m_Peer(RakNet::RakPeerInterface::GetInstance()),

			m_Factory(*this),
			m_PacketHandlers()
		{
			// Start Server
			RakNet::SocketDescriptor sd(port, 0);
			RakNet::StartupResult result = m_Peer->Startup(maxClients, &sd, 1);

			// Check if RakNet correctly started
			if (result != RakNet::RAKNET_STARTED)
				throw std::exception("RakNet failed to start");

			// Set RakNet Settings
			m_Peer->SetMaximumIncomingConnections(maxClients);

			// Log Successful Initialization
			m_Logger.LogInfo("RakNetNetwork Initialized");
		}

		RakNetNetwork::~RakNetNetwork() {
			RakNet::RakPeerInterface::DestroyInstance(m_Peer);
		}

		// Misc Network Utility Functions

		RakNet::RakPeerInterface& RakNetNetwork::GetRakPeer() { return *m_Peer; }

		// Packet Handler Utility Functions

		Network::INetworkFactory& RakNetNetwork::GetFactory() {
			return m_Factory;
		}

		void RakNetNetwork::Attach(Network::IPacketHandler& packetHandler) {
			// dynamic_cast to make sure we're dealing with a valid packet handler
			// Throws exception if invalid, like if packetHandler isn't a RakNetPacketHandler
			IRakNetPacketHandler& rakPacketHandler = dynamic_cast<IRakNetPacketHandler&>(packetHandler);

			// Since it's correct, push it into the list
			m_PacketHandlers.push_front(&rakPacketHandler);
		}

		void RakNetNetwork::Detach(Network::IPacketHandler& packetHandler) {
			auto i = m_PacketHandlers.begin();
			while (i != m_PacketHandlers.end()) {
				if ((*i) == &packetHandler) {
					// Remove Packet Handler from List
					i = m_PacketHandlers.erase(i);
					return;
				}
				else
					i++;
			}

			// Should we notify the programmer of the engine trying to detach
			// a packet handler without it being needed with a crash? Let's
			// just log a warning instead to not frustrate any users.
			m_Logger.LogWarning("Packet Handler 0x%p cannot be Detached because it's not Attached", &packetHandler);
		}

		// Network Error Reporting Functions

		void RakNetNetwork::ReportProtocolError() {
			throw std::exception("Protocol Error");
		}

		// Game Loop

		void RakNetNetwork::HandlePackets() {
			RakNet::Packet *packet;

			// Iterate through all incoming packets
			for (packet = m_Peer->Receive(); packet; m_Peer->DeallocatePacket(packet), packet = m_Peer->Receive()) {
				bool valid = true;

				// Log any useful packet that we can log
				switch (packet->data[0]) {
				case ID_NEW_INCOMING_CONNECTION: {
													 m_Logger.LogInfo("New Client Connected");

													 // Send Server Name and Version to Client
													 RakNet::BitStream bs;
													 bs.Write(GamePacketIDType::ClientLog);
													 bs.Write(Utils::LoggingLevel::Highlight);
													 bs.Write("\n ==== "APP_NAME" ==== \n"
														 "Version   "APP_VERSION"\n"
														 "Author    "APP_AUTHOR"\n"
														 STR_SUPPORT);
													 m_Peer->Send(&bs, HIGH_PRIORITY, RELIABLE, 0, packet->guid, false);
				} break;
				default:
					// Packet not found, gonna mark it invalid for now
					valid = false;
					break;
				}

				// Send Packet to Packet Handlers
				for (IRakNetPacketHandler* packetHandler : m_PacketHandlers)
					valid |= packetHandler->HandlePacket(*packet);

				// On Invalid Packet, Log it
				if (!valid)
					m_Logger.LogWarning("Message with invalid identifier %i has arrived", packet->data[0]);
			}
		}
	}
}