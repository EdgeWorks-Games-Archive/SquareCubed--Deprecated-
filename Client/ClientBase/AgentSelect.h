#pragma once

#include <memory>
#include <ClientBase/ISelectionRenderer.h>
#include <ClientBase/Input.h>

namespace Core { class Engine; }

namespace Graphics {
	class IGraphics;
	class ISelectionRenderer;
}

namespace Tools {
	namespace Agents {
		class Agents;
		class AgentSelect final {
			std::unique_ptr<Graphics::ISelectionRenderer> m_Renderer;
			Tools::Agents::Agents &m_Agents;
			Utils::EventScope m_EventScope;

			void OnMouseButtonChange(const Input::MouseEventArgs &args);
			
		public:
			AgentSelect(Core::Engine &engine, Tools::Agents::Agents &agents);
			void RenderAgentSelections();
		};
	}
}