#pragma once

#include <RakNetTypes.h>
#include <MessageIdentifiers.h>

// Naming Conventions for Packet Types
// - "Up" suffix means it's data sent from the client to the server exclusively.
//   The difference between a packet type ending with Up and one named the same but
//   without the suffix, is that an Up packet doesn't need to define player GUID
//   because the server will use the packet to retrieve the player's GUID.
//   If there's no packet type without the Up suffix it's not needed.

enum class GamePacketIDType : RakNet::MessageID {
	ClientLog = ID_USER_PACKET_ENUM + 1,

	// Client to Server Player Packets
	PlayerSpawn,
	PlayerPhysicsUpdate,

	// Server to Client Player Packets
	PlayerDesc,

	// Server to Client Agent Packets
	AgentPhysicsUpdate,
	AgentDesc,
	AgentRemove,

	WorldChunk
};

// Place any structs you need within a packet in here.
// All packets need to be byte aligned for network usage reasons.
// Remember that this does mean they're slower to access data from.
// Avoid doing too much work with these structs other then just
// getting and setting data for sending and receiving.
#pragma pack(push, 1)

#pragma pack(pop)