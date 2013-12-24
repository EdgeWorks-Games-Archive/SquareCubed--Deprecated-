#include "GameDispatcher.h"

#include "RakNetNetwork.h"

#include <CommonLib/PacketTypes.h>

#include <RakPeerInterface.h>
#include <BitStream.h>

namespace RakNetNetwork {
	// Initialization/Uninitialization

	GameDispatcher::GameDispatcher(RakNetNetwork &network) :
		m_Network(network)
	{
	}

	// Send Functions
	
	void GameDispatcher::SpawnPlayer() {

		// Build Packet to Send
		RakNet::BitStream bs;
		bs.Write(GamePacketIDType::PlayerSpawn);

		// Send the Packet to the World Server
		m_Network.GetRakPeer().Send(&bs, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, m_Network.GetWorldServer(), false);
	}
}