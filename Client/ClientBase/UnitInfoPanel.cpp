#include "UnitInfoPanel.h"

#include "Engine.h"
#include "IGUI.h"
#include "IElementFactory.h"
#include "IView.h"
#include "ILabel.h"
#include "IPanel.h"

namespace Tools {
	namespace Units {
		UnitInfoPanel::UnitInfoPanel(Core::Engine &engine, GUI::Elements::IViewGenerator &view) {
			// Create Unit Info Panel
			std::unique_ptr<GUI::Elements::IPanelGenerator> infoPanel = engine.GetGUI().GetElementFactory().CreatePanel();

			infoPanel->Size = glm::uvec2(200, 100);
			infoPanel->Position = glm::ivec2(6, 6);
			infoPanel->PositionType = GUI::Elements::PositionType::Absolute;
			infoPanel->HorizontalPos = GUI::Elements::HorizontalAlign::Right;
			infoPanel->VerticalPos = GUI::Elements::VerticalAlign::Bottom;

			// Add Name Label to Panel
			std::unique_ptr<GUI::Elements::ILabelGenerator> nameLabel = engine.GetGUI().GetElementFactory().CreateLabel();
			nameLabel->Text = "Random McRandom";
			infoPanel->Add(std::move(nameLabel));

			// Add Type Label to Panel
			std::unique_ptr<GUI::Elements::ILabelGenerator> typeLabel = engine.GetGUI().GetElementFactory().CreateLabel();

			typeLabel->Text = "Human";
			typeLabel->Italic = true;

			typeLabel->Position = glm::ivec2(6, 6);
			typeLabel->PositionType = GUI::Elements::PositionType::Relative;
			typeLabel->HorizontalPos = GUI::Elements::HorizontalAlign::Right;

			infoPanel->Add(std::move(typeLabel));

			// Add Panel
			view.Add(std::move(infoPanel));
		}
	}
}