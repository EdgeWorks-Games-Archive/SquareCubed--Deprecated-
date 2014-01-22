#pragma once

#include <ClientBase/IGameDispatcher.h>

namespace RakNetNetwork {
	class RakNetNetwork;

	class GameDispatcher final : public Network::IGameDispatcher {
		RakNetNetwork &m_Network;

	public: // Initialization/Uninitialization
		GameDispatcher(RakNetNetwork &network);

	public: // Send Functions
		void SpawnPlayer();
	};
}