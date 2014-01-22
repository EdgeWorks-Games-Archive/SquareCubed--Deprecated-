#pragma once

namespace Utils { class ILoggingManager; }

namespace Server {
	namespace Network { class INetwork; }

	namespace RakNetNetwork {
		// Use this function to create a new RakNetNetwork object without
		// including RakNetNetwork.h (and the includes that come with it)
		Network::INetwork* LoadNetwork(Utils::ILoggingManager &logManager, const int port, const int maxClients);
	}
}