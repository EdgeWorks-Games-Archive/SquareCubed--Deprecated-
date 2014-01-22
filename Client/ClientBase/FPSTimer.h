#pragma once

#include "Types.h"

#include <memory>

namespace Tools {
	namespace Misc {
		class FPSTimer final {
			std::unique_ptr<GUI::Elements::IDynamicLabel> m_Label;

		public: // Properties
			float UpdateInterval;
			float Accumulator;

		public:
			FPSTimer(Core::Engine &engine, GUI::Elements::IViewGenerator &view);
			void Update(const float delta);
		};
	}
}