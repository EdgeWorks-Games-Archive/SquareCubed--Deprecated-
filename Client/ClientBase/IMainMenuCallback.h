#pragma once

namespace Network {
	class IMainMenuCallback {
	public: // Initialization/Uninitialization
		virtual ~IMainMenuCallback() {}

	public: // Callback Functions
		virtual void ReceivedRequestAccepted() = 0;
	};
}