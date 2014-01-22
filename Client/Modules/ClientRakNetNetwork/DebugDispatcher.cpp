#ifdef _DEBUG

#include "DebugDispatcher.h"

#include "RakNetNetwork.h"

#include <CRakNetNetwork/PacketTypes.h>

#include <RakPeerInterface.h>
#include <BitStream.h>

namespace RakNetNetwork {
	// Initialization/Uninitialization

	DebugDispatcher::DebugDispatcher(RakNetNetwork &network) :
		m_Network(network)
	{
	}

	// Send Functions
	
	void DebugDispatcher::SpawnUnit(const glm::vec2 &pos) {
		// Build Packet to Send
		RakNet::BitStream bs;
		bs.Write(GamePacketIDType::DebugUnitSpawn);
		bs.Write(pos.x);
		bs.Write(pos.y);

		// Send the Packet to the World Server
		m_Network.GetRakPeer().Send(&bs, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, m_Network.GetWorldServer(), false);
	}
}

#endif