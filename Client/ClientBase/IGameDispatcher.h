#pragma once

namespace Network {
	class IGameDispatcher {
	public: // Initialization/Uninitialization
		virtual ~IGameDispatcher() {}

	public: // Send Functions
		virtual void SpawnPlayer() = 0;
	};
}