#pragma once

#include "Types.h"

namespace Tools {
	namespace Misc {
		class FPSTimer final {
		public:
			FPSTimer(GUI::IViewGenerator &view);
			void Update(const float delta);
		};
	}
}