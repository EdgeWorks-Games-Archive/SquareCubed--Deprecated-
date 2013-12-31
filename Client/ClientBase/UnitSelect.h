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
	namespace Units {
		class Units;
		class UnitSelect final {
			std::unique_ptr<Graphics::ISelectionRenderer> m_Renderer;
			Tools::Units::Units &m_Units;
			Utils::EventScope m_EventScope;
			Input::Input &m_Input;
			std::list<std::reference_wrapper<IUnit>> m_SelectedUnits;

			void OnMouseButtonChange(const Input::MouseEventArgs &args);
			
		public:
			UnitSelect(Core::Engine &engine, Tools::Units::Units &units);
			void RenderUnitSelections();
		};
	}
}