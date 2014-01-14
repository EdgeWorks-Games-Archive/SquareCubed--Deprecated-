#include "FPSTimer.h"

#include "IView.h"
#include "ILabel.h"

namespace Tools {
	namespace Misc {
		FPSTimer::FPSTimer(GUI::IViewGenerator &view) :
			m_DynamicLabel()
		{
			GUI::ILabelGenerator &label = view.AddDynamicLabel(m_DynamicLabel, "FPS: ### Delta: ###ms");
			label.PositionType = GUI::PositionType::Absolute;
		}

		void FPSTimer::Update(const float delta) {
		}
	}
}