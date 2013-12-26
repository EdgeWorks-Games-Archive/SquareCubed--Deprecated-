#include "Agents.h"
#include "INetwork.h"
#include "INetworkFactory.h"
#include "IAgentsDispatcher.h"
#include "IClientID.h"
#include "BaseAgentTypes.h"

#include "WorldServer.h"

namespace Server {
	namespace Agents {
		Agents::Agents(Core::WorldServer& server) :
			m_Server(server),
			m_Dispatcher(server.GetNetwork().GetFactory().CreateAgentsDispatcher()),
			m_Agents()
		{
			std::unique_ptr<IAgent> agent = std::make_unique<DynamicAgent>(m_Server.GetPhysics(), 10, 2.0);
			agent->SetPosition(glm::vec2(2, 1));
			AddAgent(std::move(agent));
		}

		Agents::~Agents() {
		}

		void Agents::AddAgent(std::unique_ptr<IAgent> agent) {
			m_Dispatcher->BroadcastAgentDesc(agent->ID, agent->GetHealth(), agent->GraphicId);
			m_Agents.push_front(std::move(agent));
		}

		void Agents::RemoveAgent(unsigned int agentId) {
			std::list<std::unique_ptr<IAgent>>::iterator it = m_Agents.begin();
			while (it != m_Agents.end()) {
				if ((*it)->ID == agentId) {
					// Found it!
					it = m_Agents.erase(it);

					// Oh and tell the client				
					m_Dispatcher->BroadcastAgentRemove(agentId);

					// Done!
					return;
				}
				else
					++it;
			}
		}

		void Agents::SendAllAgentDescs(const Network::IClientID &clientId) {
			for (std::unique_ptr<IAgent> &agent : m_Agents) {
				m_Dispatcher->SendAgentDesc(
					clientId,
					agent->ID,
					agent->GetHealth(),
					agent->GraphicId
				);
			}
		}

		// Game Loop

		void Agents::Update(const float delta) {
			for (std::unique_ptr<IAgent> &agent : m_Agents)
				agent->Update(delta);
		}

		void Agents::SendPackets() {
			for (std::unique_ptr<IAgent> &agent : m_Agents) {
				m_Dispatcher->BroadcastAgentPhysics(
					agent->ID,
					agent->GetDynamicRigidBody(),
					agent->Rotation
				);
			}
		}
	}
}