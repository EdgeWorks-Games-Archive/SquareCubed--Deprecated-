#include "FPSTimer.h"

#include "IView.h"
#include "ILabel.h"

#include <sstream>
#include <iomanip>

namespace Tools {
	namespace Misc {
		FPSTimer::FPSTimer(GUI::IViewGenerator &view) :
			m_Label(),
			UpdateInterval(0.5f),
			Accumulator(0.0f)
		{
			GUI::ILabelGenerator &label = view.AddDynamicLabel(m_Label, "FPS: ### Delta: ###ms");
			label.PositionType = GUI::PositionType::Absolute;
		}

		void FPSTimer::Update(const float delta) {
			Accumulator += delta;
			if (Accumulator > UpdateInterval) {
				Accumulator -= UpdateInterval;
				std::stringstream text;
				text << std::setfill('0') << std::fixed << std::setprecision(0);
				text << "FPS: " << std::setw(3) << 1.0f / delta;
				text << " Delta: " << std::setw(3) << delta * 1000.0f << "ms";
				m_Label->SetText(text.str());
			}
		}
	}
}