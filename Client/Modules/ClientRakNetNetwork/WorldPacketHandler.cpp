#include "WorldPacketHandler.h"

#include <ClientBase/INetwork.h>
#include <ClientBase/IWorldCallback.h>

#include <CommonLib/PacketTypes.h>

#include <BitStream.h>

#include <memory>

namespace RakNetNetwork {
	// Initialization/Uninitialization

	WorldPacketHandler::WorldPacketHandler(Network::INetwork &network, Network::IWorldCallback &callback) :
		m_Network(network),
		m_Callback(callback)
	{
	}

	// Game Loop

	bool WorldPacketHandler::HandlePacket(RakNet::Packet &packet) {
		switch (packet.data[0]) {
		case (int) GamePacketIDType::WorldChunk: {
			// Set up BitStream
			RakNet::BitStream bs(packet.data, packet.length, false);
			bs.IgnoreBytes(sizeof(RakNet::MessageID));

			// Get the Data
			DataTypes::Chunk chunk(0, 0);
			bs.Read(chunk.X);
			bs.Read(chunk.Y);
			bool s;
			for (unsigned int x = 0; x < chunk.CHUNK_MAX_SIZE; x++) {
				for (unsigned int y = 0; y < chunk.CHUNK_MAX_SIZE; y++) {
					s = bs.Read(chunk.Terrain[x][y]);
				}
			}

			// Make sure the packet is correctly received
			if (!s) {
				m_Network.ReportProtocolError();
				return true;
			}

			// Call the Callback Function
			m_Callback.ReceivedWorldChunk(std::move(chunk));
			} return true;
		}

		return false;
	}
}