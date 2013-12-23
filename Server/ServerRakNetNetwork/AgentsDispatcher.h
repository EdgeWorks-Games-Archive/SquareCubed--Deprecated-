#pragma once

#include <WorldServerBase/IAgentsDispatcher.h>
#include <WorldServerBase/IClientID.h>

#include <RakPeer.h>

namespace Server {
	namespace RakNetNetwork {
		class RakNetNetwork;

		class AgentsDispatcher final : public Network::IAgentsDispatcher {
			RakNetNetwork &m_Network;

		public: // Initialization/Uninitialization
			AgentsDispatcher(RakNetNetwork &network);

		public: // Send Functions
			void BroadcastAgentPhysics(const unsigned int agentId, const Physics::DynamicRigidBody &rigidBody, const float rotation);
			void BroadcastAgentDesc(unsigned int agentId, DataTypes::Health health, unsigned int graphicId);
			void BroadcastAgentRemove(unsigned int agentId);
			void SendAgentDesc(const Network::IClientID &clientId, unsigned int agentId, DataTypes::Health health, unsigned int graphicId);

		private: // Internal Send Functions
			void RakSendAgentDesc(const RakNet::RakNetGUID &guid, bool broadcast, unsigned int agentId, DataTypes::Health health, unsigned int graphicId);
		};
	}
}