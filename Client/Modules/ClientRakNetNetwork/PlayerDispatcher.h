#pragma once

#include <ClientBase/IPlayerDispatcher.h>

namespace RakNetNetwork {
	class RakNetNetwork;

	class PlayerDispatcher final : public Network::IPlayerDispatcher {
		RakNetNetwork &m_Network;

	public: // Initialization/Uninitialization
		PlayerDispatcher(RakNetNetwork &network);

	public: // Send Functions
		void SendPlayerPhysics(const Physics::DynamicRigidBody &rigidBody, const float rotation);
	};
}