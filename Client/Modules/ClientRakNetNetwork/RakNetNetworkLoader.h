#pragma once

namespace Network { class INetwork; }
namespace Utils { class ILoggingManager; }

namespace RakNetNetwork {
	// Use this function to create a new RakNetNetwork object without
	// including RakNetNetwork.h (and the includes that come with it)
	Network::INetwork* LoadNetwork(Utils::ILoggingManager &logManager);
}