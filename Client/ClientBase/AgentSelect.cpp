#include "AgentSelect.h"

#include <ClientBase/Agents.h>
#include <ClientBase/Engine.h>

#include <ClientBase/IGraphics.h>
#include <ClientBase/IGraphicsFactory.h>

namespace Tools {
	namespace Agents {
		AgentSelect::AgentSelect(Core::Engine &engine, Tools::Agents::Agents &agents) :
			m_Renderer(engine.GetGraphics().GetFactory().CreateSelectionRenderer()),
			m_Agents(agents),
			m_EventScope()
		{
			engine.GetInput().OnMouseButtonChange.AttachMember(this, &AgentSelect::OnMouseButtonChange, m_EventScope);
		}

		void AgentSelect::RenderAgentSelections()
		{
			m_Renderer->RenderSelectionBoxes(m_Agents.GetAllAgents());
		}

		void AgentSelect::OnMouseButtonChange(const Input::MouseEventArgs &args) {
			if (args.IsLeftButtonDown)
				printf("wow you pressed the left mouse button well done\n");
			if (args.IsRightButtonDown)
				printf("wow you pressed the right mouse button well done\n");
		}
	}
}