#include "FPSTimer.h"

#include "IView.h"
#include "ILabel.h"

namespace Tools {
	namespace Misc {
		FPSTimer::FPSTimer(GUI::IViewGenerator &view) {
			GUI::ILabelGenerator &label = view.AddLabel("FPS: ### Delta: ###ms");
			label.PositionType = GUI::PositionType::Absolute;
		}

		void FPSTimer::Update(const float delta) {
		}
	}
}