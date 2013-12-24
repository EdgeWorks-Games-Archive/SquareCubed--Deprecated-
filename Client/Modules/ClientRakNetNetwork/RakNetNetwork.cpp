#include "RakNetNetwork.h"
#include "RakNetNetworkLoader.h"

#include "IRakNetPacketHandler.h"

#include <CommonLib/PacketTypes.h>
#include <CommonLib/ILoggingManager.h>

#include <RakPeerInterface.h>
#include <BitStream.h>

namespace RakNetNetwork {
	// Factory to avoid including the big compiler-grinding-to-a-crawl file
	Network::INetwork* LoadNetwork(Utils::ILoggingManager &logManager) { return new RakNetNetwork(logManager); }

	// Initialization/Uninitialization

	RakNetNetwork::RakNetNetwork(Utils::ILoggingManager &logManager) :
		m_Logger(logManager.CreateLogger("Network")),
		m_Peer(nullptr),

		m_WorldServerGUID(),

		m_Factory(*this),
		m_PacketHandlers()
	{
	}

	RakNetNetwork::~RakNetNetwork() {
	}

	// Misc Network Utility Functions

	bool RakNetNetwork::Connect(const char* host, const int port) {
		// Start RakNet
		m_Peer = RakNet::RakPeerInterface::GetInstance();
		RakNet::SocketDescriptor sd;
		RakNet::StartupResult sResult = m_Peer->Startup(1, &sd, 1);

		// Check if RakNet correctly started
		if (sResult != RakNet::RAKNET_STARTED)
			return false;

		// Connect to Server
		RakNet::ConnectionAttemptResult cResult = m_Peer->Connect(host, port, 0, 0);
		if (cResult != RakNet::CONNECTION_ATTEMPT_STARTED)
			return false;

		m_Logger.LogInfo("Connection request sent!");
		return true;
	}

	void RakNetNetwork::Disconnect() {
		if (m_Peer != nullptr) {
			m_Peer->Shutdown(1000, 0, MEDIUM_PRIORITY);
			RakNet::RakPeerInterface::DestroyInstance(m_Peer);
			m_Peer = nullptr;
		}
	}

	RakNet::RakPeerInterface& RakNetNetwork::GetRakPeer() { return *m_Peer; }
	RakNet::RakNetGUID& RakNetNetwork::GetWorldServer() { return m_WorldServerGUID; }

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
		if (m_Peer != nullptr) {
			RakNet::Packet *packet;

			// Iterate through all incoming packets
			for (packet = m_Peer->Receive(); packet; m_Peer->DeallocatePacket(packet), packet = m_Peer->Receive()) {
				bool valid = true;

				// Log any useful packet that we can log
				switch (packet->data[0]) {
				case ID_CONNECTION_REQUEST_ACCEPTED:
					// World server accepted our connection
					m_Logger.LogInfo("Connection request accepted!");
					m_WorldServerGUID = packet->guid;
					break;
				case (int) GamePacketIDType::ClientLog: {
					// Set up BitStream
					RakNet::BitStream bs(packet->data, packet->length, false);
					bs.IgnoreBytes(sizeof(RakNet::MessageID));

					// Read Logging Level from BitStream
					Utils::LoggingLevel level;
					bs.Read(level);

					// Read String from BitStream
					RakNet::RakString rs;
					bs.Read(rs);

					// Send String to Logger
					char buff[400];
					sprintf_s(buff, 400, "Server: %s", rs.C_String());
					m_Logger.LogLevel(buff, level);
					} break;
				default:
					// Packet not found, gonna mark it invalid for now
					valid = false;
					break;
				}

				// Send Packet to Packet Handlers
				for (IRakNetPacketHandler* packetHandler : m_PacketHandlers)
					valid |= packetHandler->HandlePacket(*packet);

				if (!valid) {
					// Invalid Packet, Log it
					char buff[400];
					sprintf_s(buff, "Message with invalid identifier %i has arrived!", packet->data[0]);
					m_Logger.LogWarning(buff);
				}
			}
		}
	}
}