#pragma once

#include "Types.h"
#include "ISelectionRenderer.h"
#include "Input.h"

#include "UnitInfoPanel.h"

#include <memory>

namespace Tools {
	namespace Units {
		class UnitSelect final {
			// External Components
			Tools::Units::Units &m_Units;
			Input::Input &m_Input;

			// Internal Components
			UnitInfoPanel m_InfoPanel;
			std::unique_ptr<Graphics::ISelectionRenderer> m_Renderer;
			std::unique_ptr<Network::IUnitSelectDispatcher> m_Dispatcher;

			Utils::EventScope m_EventScope;
			std::list<std::reference_wrapper<IUnit>> m_SelectedUnits, m_ControlGroup[9];
			glm::vec2 m_OriginalCursorPos;
			bool m_CurrentlyHolding = false;

			Input::KeyID Key[9];

		public: // Initialization/Uninitialization
			UnitSelect(Core::Engine &engine, GUI::Elements::IViewGenerator &view, Tools::Units::Units &units);
			~UnitSelect();

		private: // Internal Helper Functions
			bool IsUnitSelected(const UnitID unitId);
			void Deselect(const UnitID unitId);

		private: // Event Callbacks
			void OnMouseButtonChange(const Input::MouseEventArgs &args);
			void OnKeyChange(const Input::KeyChangeEventArgs &args);

		public: // Game Loop
			void Render();
		};
	}
}