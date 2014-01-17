#pragma once

#include "IElement.h"

#include <glm/glm.hpp>

#include <string>

namespace GUI {
	namespace Elements {
		/// Static Label ///

		/** Generates a static label, does not give you a binding object. */
		class ILabelGenerator : public virtual IElementGenerator {
		public:
			ILabelGenerator() :
				Text(),
				Italic(false)
			{}
			virtual ~ILabelGenerator() {}

		public: // Properties
			std::string Text;

			bool Italic;
		};

		/// Dynamic Label ///

		class IDynamicLabel {
		public:
			virtual ~IDynamicLabel() {}
			virtual void SetText(std::string text) = 0;
		};

		class IDynamicLabelGenerator : public virtual ILabelGenerator {
		public:
			virtual ~IDynamicLabelGenerator() {}
		};
	}
}