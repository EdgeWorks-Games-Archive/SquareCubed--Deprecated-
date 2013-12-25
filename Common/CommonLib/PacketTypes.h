#pragma once

#include <RakNetTypes.h>
#include <MessageIdentifiers.h>

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