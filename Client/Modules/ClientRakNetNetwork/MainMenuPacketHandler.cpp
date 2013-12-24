#include "MainMenuPacketHandler.h"

#include <ClientBase/IMainMenuCallback.h>

#include <RakNetTypes.h>
#include <MessageIdentifiers.h>

namespace RakNetNetwork {
	// Initialization/Uninitialization

	MainMenuPacketHandler::MainMenuPacketHandler(Network::IMainMenuCallback &callback) :
		m_Callback(callback)
	{
	}

	// Game Loop

	bool MainMenuPacketHandler::HandlePacket(RakNet::Packet &packet) {
		switch (packet.data[0]) {
		case ID_CONNECTION_REQUEST_ACCEPTED:
			m_Callback.ReceivedRequestAccepted();
			return true;
		}

		return false;
	}
}