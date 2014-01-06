#pragma once

#include "Types.h"
#include "ISelectionRenderer.h"
#include "Input.h"

#include <memory>

namespace Tools {
	namespace Units {
		class Units;
		class UnitSelect final {
			std::unique_ptr<Graphics::ISelectionRenderer> m_Renderer;
			Tools::Units::Units &m_Units;
			Utils::EventScope m_EventScope;
			Input::Input &m_Input;
			std::list<std::reference_wrapper<IUnit>> m_SelectedUnits, m_ControlGroup[9];
			std::unique_ptr<Network::IUnitSelectDispatcher> m_Dispatcher;
			glm::vec2 m_OriginalCursorPos;
			bool m_CurrentlyHolding = false;

			Input::KeyID Key[9];

		public: // Initialization/Uninitialization
			UnitSelect(Core::Engine &engine, Tools::Units::Units &units);
			~UnitSelect();

		private: // Internal Helper Functions
			bool IsUnitSelected(const UnitID unitId);

		private: // Event Callbacks
			void OnMouseButtonChange(const Input::MouseEventArgs &args);
			void OnKeyChange(const Input::KeyChangeEventArgs &args);

		public: // Game Loop
			void Render();
		};
	}
}