#include "UnitSelect.h"

#include <ClientBase/Units.h>
#include <ClientBase/Engine.h>

#include <ClientBase/IGraphics.h>
#include <ClientBase/IGraphicsFactory.h>

namespace Tools {
	namespace Units {
		UnitSelect::UnitSelect(Core::Engine &engine, Tools::Units::Units &units) :
			m_Renderer(engine.GetGraphics().GetFactory().CreateSelectionRenderer()),
			m_Units(units),
			m_EventScope()
		{
			engine.GetInput().OnMouseButtonChange.AttachMember(this, &UnitSelect::OnMouseButtonChange, m_EventScope);
		}

		void UnitSelect::RenderUnitSelections()
		{
			m_Renderer->RenderUnitSelection(m_Units.GetAllUnits());
			//m_Renderer->RenderSelectionBox(glm::vec2(2, 2), glm::vec2(3, 2));
		}

		void UnitSelect::OnMouseButtonChange(const Input::MouseEventArgs &args) {
			if (args.MouseButton == Input::MouseButton::Left && args.IsPressed)
				printf("wow you pressed the left mouse button well done\n");
			if (args.MouseButton == Input::MouseButton::Right && args.IsPressed)
				printf("wow you pressed the right mouse button well done\n");
		}
	}
}