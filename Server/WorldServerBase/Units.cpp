#include "Units.h"
#include "INetwork.h"
#include "INetworkFactory.h"
#include "IUnitsDispatcher.h"
#include "IClientID.h"
#include "BaseUnitTypes.h"

#include "WorldServer.h"

namespace Server {
	namespace Units {
		Units::Units(Core::WorldServer& server) :
			m_Server(server),
			m_Dispatcher(server.GetNetwork().GetFactory().CreateUnitsDispatcher()),
			m_Units()
		{
		}

		Units::~Units() {
		}

		void Units::AddUnit(std::unique_ptr<Unit> unit) {
			m_Dispatcher->BroadcastUnitDesc(unit->ID, unit->GetHealth(), unit->GraphicId);
			m_Units.push_front(std::move(unit));
		}

		void Units::RemoveUnit(unsigned int unitId) {
			std::list<std::unique_ptr<Unit>>::iterator it = m_Units.begin();
			while (it != m_Units.end()) {
				if ((*it)->ID == unitId) {
					// Found it!
					it = m_Units.erase(it);

					// Oh and tell the client				
					m_Dispatcher->BroadcastUnitRemove(unitId);

					// Done!
					return;
				}
				else
					++it;
			}
		}

		void Units::SendAllUnitDescs(const Network::IClientID &clientId) {
			for (std::unique_ptr<Unit> &unit : m_Units) {
				m_Dispatcher->SendUnitDesc(
					clientId,
					unit->ID,
					unit->GetHealth(),
					unit->GraphicId
				);
			}
		}

		// Game Loop

		void Units::Update(const float delta) {
			for (std::unique_ptr<Unit> &unit : m_Units)
				unit->Update(delta);
		}

		void Units::SendPackets() {
			for (std::unique_ptr<Unit> &unit : m_Units) {
				m_Dispatcher->BroadcastUnitPhysics(
					unit->ID,
					unit->GetDynamicRigidBody(),
					unit->Rotation
				);
			}
		}
	}
}