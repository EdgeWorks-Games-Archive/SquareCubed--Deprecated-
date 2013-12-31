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
			m_EventScope(),
			m_Input(engine.GetInput()),
			m_SelectedUnits()
		{
			engine.GetInput().OnMouseButtonChange.AttachMember(this, &UnitSelect::OnMouseButtonChange, m_EventScope);
		}

		void UnitSelect::RenderUnitSelections()
		{
			m_Renderer->RenderUnitSelection(m_SelectedUnits);
		}

		void UnitSelect::OnMouseButtonChange(const Input::MouseEventArgs &args) {
			if (args.MouseButton == Input::MouseButton::Left && args.IsPressed) {
				const std::list<std::unique_ptr<IUnit>>& unitList = m_Units.GetAll();

				for (const std::unique_ptr<IUnit> &unit : unitList) {
					auto dUnit = static_cast<const DynamicUnit*>(unit.get());
					if (dUnit->RigidBody.BroadphaseAABB.Contains(m_Input.GetCursorPosition().World)) {
						m_SelectedUnits.push_back(*unit);
					}
					else {
						m_SelectedUnits.clear();
					}
				}
			}
			
			if (args.MouseButton == Input::MouseButton::Right && args.IsPressed)
				printf("wow you pressed the right mouse button well done\n");
		}
	}
}