#include "FPSTimer.h"

#include "IView.h"
#include "ILabel.h"
#include "IPanel.h"

#include <sstream>
#include <iomanip>

namespace Tools {
	namespace Misc {
		FPSTimer::FPSTimer(GUI::IViewGenerator &view) :
			m_Label(),
			UpdateInterval(0.5f),
			Accumulator(0.0f)
		{
			GUI::ILabelGenerator &label = view.AddDynamicLabel(m_Label, "FPS: 060 Delta: 016ms");
			label.PositionType = GUI::PositionType::Absolute;
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