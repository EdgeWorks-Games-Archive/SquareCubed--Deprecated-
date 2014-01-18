#pragma once

#include "IElement.h"

namespace GUI {
	namespace Elements {
		class IProgressBarGenerator : public virtual IElementGenerator {
		public: // Initialization/Uninitialization
			IProgressBarGenerator() :
				Width(100)
			{}

		public: // Properties
			unsigned int Width;
		};
	}
}