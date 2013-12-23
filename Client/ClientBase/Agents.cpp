#include "Agents.h"

#include <ClientBase/IGraphics.h>
#include <ClientBase/IGraphicsFactory.h>
#include <ClientBase/IAgentRenderer.h>
#include <ClientBase/INetwork.h>
#include <ClientBase/INetworkFactory.h>
#include <ClientBase/IPacketHandler.h>

namespace Tools {
	namespace Agents {
		// Initialization/Uninitialization

		Agents::Agents(Network::INetwork &networkFactory, Graphics::IGraphics &graphics, Physics::Physics &physics, std::string tileArrayPath) :
			m_Renderer(graphics.GetFactory().CreateAgentRenderer(
				graphics.GetFactory().GetTileArray(tileArrayPath)
			)),

			m_Network(networkFactory),
			m_Handler(m_Network.GetFactory().CreateAgentsHandler(*this)),

			m_Agents(),

			m_Physics(physics)
		{
			m_Network.Attach(*m_Handler);
		}

		Agents::~Agents() {
			m_Network.Detach(*m_Handler);
		}

		// Agents Management Utility Functions

		void Agents::AddAgent(IAgent *agent) {
			m_Agents.push_front(std::unique_ptr<IAgent>(agent));
		}

		void Agents::RemoveAgent(AgentID agentId) {
			auto it = m_Agents.begin();
			while (it != m_Agents.end()) {
				if ((*it)->ID == agentId) {
					// Found it!
					it = m_Agents.erase(it);
					return;
				}
				else
					++it;
			}
		}

		void Agents::UpdateAgent(AgentID agentId, DataTypes::Health health, unsigned int graphicId) {
			for (std::unique_ptr<IAgent> &agent : m_Agents) {
				if (agent->ID == agentId) {
					// Update Agent Data
					agent->GraphicID = std::move(graphicId);
					agent->Health = std::move(health);
					return;
				}
			}

			// Not found, throw Exception
			throw std::exception("Agent not Found");
		}

		bool Agents::AgentExists(AgentID agentId) {
			for (std::unique_ptr<IAgent> &agent : m_Agents) {
				if (agent->ID == agentId)
					return true;
			}

			// Not found, return false
			return false;
		}

		// Game Loop

		void Agents::RenderAgents() {
			m_Renderer->RenderAgents(m_Agents);
		}

		// Callback Functions

		void Agents::ReceivedUpdateAgentPhysics(const unsigned int agentId, const CNetwork::PhysicsUpdateData &data) {
			for (std::unique_ptr<IAgent> &agent : m_Agents) {
				if (agent->ID == agentId) {
					// Update the Agent's Position
					agent->ReceivedUpdatePhysics(data);
					return;
				}
			}
		}

		void Agents::ReceivedAgentDesc(unsigned int agentId, DataTypes::Health health, unsigned int graphicId) {
			// Add new Agent if it doesn't exist
			// TODO: change this to GetPlayer returning a pointer instead that can be nullptr
			if (!AgentExists(agentId))
				AddAgent(new PhysicsAgent(agentId, health, m_Physics));

			// Update the (newly created?) Agent
			UpdateAgent(agentId, std::move(health), graphicId);
		}

		void Agents::ReceivedRemoveAgent(unsigned int agentId) {
			// Remove the Agent
			RemoveAgent(agentId);
		}
	}
}