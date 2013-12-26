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
			m_Renderer->RenderSelectionBoxes(m_Units.GetAllUnits());
		}

		void UnitSelect::OnMouseButtonChange(const Input::MouseEventArgs &args) {
			if (args.IsLeftButtonDown)
				printf("wow you pressed the left mouse button well done\n");
			if (args.IsRightButtonDown)
				printf("wow you pressed the right mouse button well done\n");
		}
	}
}