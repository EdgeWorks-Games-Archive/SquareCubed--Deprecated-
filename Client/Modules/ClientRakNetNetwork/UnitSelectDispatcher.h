#pragma once

#include <ClientBase/IUnitSelectDispatcher.h>

namespace RakNetNetwork {
	class RakNetNetwork;

	class UnitSelectDispatcher final : public Network::IUnitSelectDispatcher {
		RakNetNetwork &m_Network;

	public: // Initialization/Uninitialization
		UnitSelectDispatcher(RakNetNetwork &network);

	public: // Send Functions
		void SendMoveOrder(Tools::Units::UnitID id, const glm::vec2 &pos);
	};
}