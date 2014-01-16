#pragma once

#include "IElement.h"

#include <glm/glm.hpp>

#include <string>

namespace GUI {
	/// Static Label ///

	/** Generates a static label, does not give you a binding object. */
	class ILabelGenerator : public IElementGenerator {
	public:
		ILabelGenerator() :
			Text()
		{}
		virtual ~ILabelGenerator() {}

	public: // Properties
		std::string Text;
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