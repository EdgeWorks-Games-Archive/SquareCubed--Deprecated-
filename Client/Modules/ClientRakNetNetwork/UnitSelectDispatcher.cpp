#include "UnitSelectDispatcher.h"

#include "RakNetNetwork.h"

#include <CRakNetNetwork/PacketTypes.h>

#include <RakPeerInterface.h>
#include <BitStream.h>

namespace RakNetNetwork {
	// Initialization/Uninitialization

	UnitSelectDispatcher::UnitSelectDispatcher(RakNetNetwork &network) :
		m_Network(network)
	{
	}

	// Send Functions
	
	void UnitSelectDispatcher::SendMoveOrder(Tools::Units::UnitID id, const glm::vec2 &pos) {
		// Build Packet to Send
		RakNet::BitStream bs;
		bs.Write(GamePacketIDType::UnitOrder);
		bs.Write(id);
		bs.Write(pos.x);
		bs.Write(pos.y);

		// Send the Packet to the World Server
		m_Network.GetRakPeer().Send(&bs, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, m_Network.GetWorldServer(), false);
	}
}