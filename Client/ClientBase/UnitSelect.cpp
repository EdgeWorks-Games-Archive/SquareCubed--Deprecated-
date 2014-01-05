#include "UnitSelect.h"

#include "Units.h"
#include "Engine.h"
#include "IGraphics.h"
#include "IGraphicsFactory.h"
#include "INetwork.h"
#include "INetworkFactory.h"
#include "IUnitSelectDispatcher.h"

namespace Tools {
	namespace Units {
		UnitSelect::UnitSelect(Core::Engine &engine, Tools::Units::Units &units) :
			m_Renderer(engine.GetGraphics().GetFactory().CreateSelectionRenderer()),
			m_Units(units),
			m_EventScope(),
			m_Input(engine.GetInput()),
			m_SelectedUnits(),
			m_Dispatcher(engine.GetNetwork().GetFactory().CreateUnitSelectDispatcher()),
			m_ControlGroup()
		{
			engine.GetInput().OnMouseButtonChange.AttachMember(this, &UnitSelect::OnMouseButtonChange, m_EventScope);
			engine.GetInput().OnKeyChange.AttachMember(this, &UnitSelect::OnKeyChange, m_EventScope);

			for (int i = 0; i < 9; i++)
				Key[i] = m_Input.GetKeyId('1' + i);
		}

		UnitSelect::~UnitSelect() {}

		void UnitSelect::Render()
		{
			m_Renderer->RenderUnitSelection(m_SelectedUnits);
		}

		// Internal Helper Functions

		bool UnitSelect::IsUnitSelected(const UnitID unitId) {
			for (auto unit : m_SelectedUnits) {
				if (unit.get().ID == unitId) {
					// Found it!
					return true;
				}
			}

			// Didn't find it
			return false;
		}

		// Event Callbacks

		void UnitSelect::OnMouseButtonChange(const Input::MouseEventArgs &args) {
			if (args.MouseButton == Input::MouseButton::Left && args.IsPressed) {
				const std::list<std::unique_ptr<IUnit>>& unitList = m_Units.GetAll();
				bool noHit = true;

				// Something already selected, not holding shift for multiselection
				if (!m_Input.GetKeyMods().Shift && !m_SelectedUnits.empty())
					m_SelectedUnits.clear();

				for (const std::unique_ptr<IUnit> &unit : unitList) {
					// TODO: Needs common rigidbody interface but for now this works
					auto dUnit = static_cast<const DynamicUnit*>(unit.get());
					if (dUnit->RigidBody.BroadphaseAABB.Contains(m_Input.GetCursorPosition().World)) {
						// Either way, we need to make sure the selection list isn't cleared.
						noHit = false;

						// Only select the unit if it isn't selected already..
						if (!IsUnitSelected(unit.get()->ID))
							m_SelectedUnits.push_back(*unit);
						
						/* Unless of course we're multiselecting,
						   for which we might just want to be removing one of the units. */
						else if (m_Input.GetKeyMods().Shift) {
							auto it = m_SelectedUnits.begin();
							while (it != m_SelectedUnits.end()) {
								if ((it)->get().ID == dUnit->ID) {
									// Unit is no longer one of The Selected.
									it = m_SelectedUnits.erase(it);
								}
								else
									++it;
							}
						}
					}
				}
				// If no unit was hit at all during the click, that is a call for a selection clear.
				if (noHit && !m_Input.GetKeyMods().Shift)
					m_SelectedUnits.clear();
			}

			if (args.MouseButton == Input::MouseButton::Right && args.IsPressed) {
				// Simple move order.
				for (auto unit : m_SelectedUnits) {
					m_Dispatcher->SendMoveOrder(unit.get().ID, m_Input.GetCursorPosition().World);
				}
			}
		}
		
		void UnitSelect::OnKeyChange(const Input::KeyChangeEventArgs &args) {
			for (int i = 0; i < 9; i++) {			
				if (args.KeyId == Key[i] && m_Input.GetKeyMods().Control)
					m_ControlGroup[i] = m_SelectedUnits;
				if (args.KeyId == Key[i] && !m_Input.GetKeyMods().Control)
					m_SelectedUnits = m_ControlGroup[i];
			}
		}
	}
}