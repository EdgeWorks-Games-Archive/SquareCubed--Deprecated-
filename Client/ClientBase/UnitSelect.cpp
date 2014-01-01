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
				bool noHit = true;

				// Something already selected, not holding shift for multi-selection
				if (!m_Input.GetKeyMods().Shift && !m_SelectedUnits.empty())
					m_SelectedUnits.clear();

				for (const std::unique_ptr<IUnit> &unit : unitList) {
					// TODO: Needs common rigidbody interface but for now this works
					auto dUnit = static_cast<const DynamicUnit*>(unit.get());
					if (dUnit->RigidBody.BroadphaseAABB.Contains(m_Input.GetCursorPosition().World)) {
						// If it's already in the list then selecting it twice is kindof pointless
						bool inList = false;
						auto it = m_SelectedUnits.begin();
						while (it != m_SelectedUnits.end()) {
							if (it->get().ID == unit->ID) {
								// Found it!
								inList = true;
								noHit = false;
								break;
							}
							else
								++it;
						}
						// However - if it isn't, we do want to select it.
						if (!inList) {
							m_SelectedUnits.push_back(*unit);
							noHit = false;
						}
					}
				}
				// If no unit was hit at all during the click, that is a call for a selection clear.
				if (noHit)
					m_SelectedUnits.clear();
			}

			if (args.MouseButton == Input::MouseButton::Right && args.IsPressed) {
				printf("wow you pressed the right mouse button well done\n");
			}
		}
	}
}