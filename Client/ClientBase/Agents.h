#pragma once

#include <ClientBase/IAgentsCallback.h>
#include <ClientBase/BaseAgentTypes.h>

#include <memory>
#include <list>
#include <functional>

namespace Graphics {
	class IGraphics;
	class IAgentRenderer;
	class ITileArray;
}

namespace Network {
	class INetwork;
	class IPacketHandler;
}

namespace Physics {
	class Physics;
}

namespace Tools {
	namespace Agents {
		class Agents final : public Network::IAgentsCallback {
			// Renderer
			std::unique_ptr<Graphics::IAgentRenderer> m_Renderer;

			// Networking
			Network::INetwork &m_Network;
			std::unique_ptr<Network::IPacketHandler> m_Handler;

			// Agents Container
			std::list<std::unique_ptr<IAgent>> m_Agents;

			// External Modules
			Physics::Physics &m_Physics;

		public: // Initialization/Uninitialization
			Agents(Network::INetwork &networkFactory, Graphics::IGraphics &graphics, Physics::Physics &physics, std::string tileArrayPath);
			~Agents();

		public: // Agents Management Utility Functions
			void AddAgent(IAgent *agent);
			void RemoveAgent(AgentID agentId);
			void UpdateAgent(AgentID agentId, DataTypes::Health health, unsigned int graphicId);

			bool AgentExists(AgentID agentId);
			const std::list<std::unique_ptr<IAgent>>& GetAllAgents();

		public: // Game Loop
			void RenderAgents();
			
		public: // Callback Functions
			void ReceivedUpdateAgentPhysics(const unsigned int agentId, const CNetwork::PhysicsUpdateData &data);
			void ReceivedAgentDesc(unsigned int agentId, DataTypes::Health health, unsigned int graphicId);
			void ReceivedRemoveAgent(unsigned int agentId);
		};
	}
}