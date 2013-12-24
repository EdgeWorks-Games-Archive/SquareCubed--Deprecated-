#include "PlayerDispatcher.h"

#include "RakNetNetwork.h"

#include <CommonLib/PacketTypes.h>

#include <RakPeerInterface.h>
#include <BitStream.h>

namespace RakNetNetwork {
	// Initialization/Uninitialization

	PlayerDispatcher::PlayerDispatcher(RakNetNetwork &network) :
		m_Network(network)
	{
	}

	// Send Functions

	void PlayerDispatcher::SendPlayerPhysics(const Physics::DynamicRigidBody &rigidBody, const float rotation) {
		// Start Building Packet to Send
		RakNet::BitStream bs;

		// Add Packet ID
		bs.Write(GamePacketIDType::PlayerPhysicsUpdate);

		// Add Positon and Rotation Data
		// This is added to prevent client and server being out of sync
		bs.Write(rigidBody.Position.x);
		bs.Write(rigidBody.Position.y);
		bs.Write(rotation);

		// Add Force and Velocity Data
		bs.Write(rigidBody.Force.x);
		bs.Write(rigidBody.Force.y);
		bs.Write(rigidBody.Velocity.x);
		bs.Write(rigidBody.Velocity.y);

		// Send the Packet to the World Server
		// UNRELIABLE_SEQUENCED might not be good enough for this, if
		// it doesn't work well enough use RELIABLE_SEQUENCED instead
		m_Network.GetRakPeer().Send(&bs, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 1, m_Network.GetWorldServer(), false);
	}
}