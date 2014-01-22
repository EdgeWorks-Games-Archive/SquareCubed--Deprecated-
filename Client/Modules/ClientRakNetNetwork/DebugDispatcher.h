#pragma once

#ifdef _DEBUG

#include <ClientBase/IDebugDispatcher.h>

namespace RakNetNetwork {
	class RakNetNetwork;

	class DebugDispatcher final : public Network::IDebugDispatcher {
		RakNetNetwork &m_Network;

	public: // Initialization/Uninitialization
		DebugDispatcher(RakNetNetwork &network);

	public: // Send Functions
		void SpawnUnit(const glm::vec2 &pos);
	};
}

#endif