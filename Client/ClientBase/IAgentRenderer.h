#pragma once

#include <list>
#include <memory>

namespace Tools {
	namespace Agents { class IAgent; }
}

namespace Graphics {
	class IAgentRenderer {
	public: // Initialization/Uninitialization
		virtual ~IAgentRenderer() {}

	public: // Rendering Functions
		virtual void RenderAgents(const std::list<std::unique_ptr<Tools::Agents::IAgent>> &agents) = 0;
	};
}