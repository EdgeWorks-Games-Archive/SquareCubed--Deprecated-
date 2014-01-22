#pragma once

#include "IElement.h"

namespace GUI {
	namespace Elements {
		class IProgressBarGenerator : public virtual IElementGenerator {
		public: // Initialization/Uninitialization
			IProgressBarGenerator() :
				Label(),
				LabelWidth(0),

				Value(0),
				Max(0),

				Width(100),
				Color(ColorType::None)
			{}

		public: // Properties
			std::string Label;
			unsigned int LabelWidth;

			unsigned int Value;
			/** Max value of the progress bar. (0 = indeterminate) */
			unsigned int Max;

			unsigned int Width;
			ColorType Color;
		};
	}
}