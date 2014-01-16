#include "FPSTimer.h"

#include "Engine.h"
#include "IGUI.h"
#include "IElementFactory.h"
#include "IView.h"
#include "ILabel.h"
#include "IPanel.h"

#include <sstream>
#include <iomanip>

namespace Tools {
	namespace Misc {
		FPSTimer::FPSTimer(Core::Engine &engine, GUI::IViewGenerator &view) :
			m_Label(),
			UpdateInterval(0.5f),
			Accumulator(0.0f)
		{
			std::unique_ptr<GUI::ILabelGenerator> label = engine.GetGUI().GetElementFactory().CreateDynamicLabel(m_Label);
			label->PositionType = GUI::PositionType::Absolute;
			view.Add(std::move(label));
		}

		void FPSTimer::Update(const float delta) {
			Accumulator += delta;
			if (Accumulator >= UpdateInterval) {
				Accumulator -= UpdateInterval;

				// Build the New String
				std::stringstream text;
				text << std::setfill('0') << std::fixed << std::setprecision(0);
				text << "FPS: " << std::setw(3) << 1.0f / delta;
				text << " Delta: " << std::setw(3) << delta * 1000.0f << "ms";

				// Set the New String
				m_Label->SetText(text.str());
			}
		}
	}
}