#pragma once

#include "Types.h"

#include <memory>

namespace Tools {
	namespace Misc {
		class FPSTimer final {
			std::unique_ptr<GUI::IDynamicLabel> m_DynamicLabel;

		public:
			FPSTimer(GUI::IViewGenerator &view);
			void Update(const float delta);
		};
	}
}