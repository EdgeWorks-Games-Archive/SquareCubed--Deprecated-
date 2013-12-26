#pragma once

#include <WorldServerBase/IUnitsDispatcher.h>
#include <WorldServerBase/IClientID.h>

#include <RakPeer.h>

namespace Server {
	namespace RakNetNetwork {
		class RakNetNetwork;

		class UnitsDispatcher final : public Network::IUnitsDispatcher {
			RakNetNetwork &m_Network;

		public: // Initialization/Uninitialization
			UnitsDispatcher(RakNetNetwork &network);

		public: // Send Functions
			void BroadcastUnitPhysics(const unsigned int unitId, const Physics::DynamicRigidBody &rigidBody, const float rotation);
			void BroadcastUnitDesc(unsigned int unitId, DataTypes::Health health, unsigned int graphicId);
			void BroadcastUnitRemove(unsigned int unitId);
			void SendUnitDesc(const Network::IClientID &clientId, unsigned int unitId, DataTypes::Health health, unsigned int graphicId);

		private: // Internal Send Functions
			void RakSendUnitDesc(const RakNet::RakNetGUID &guid, bool broadcast, unsigned int unitId, DataTypes::Health health, unsigned int graphicId);
		};
	}
}