#pragma once

#include "Types.h"

#include <memory>

namespace GUI {
	class IElementFactory {
	public:
		virtual ~IElementFactory() {}

		/** Creates a new Dynamic Label Generator.
		 * \param[in,out] bindingObjPtr Pointer that the binding object will be assigned to.
		 * \return A new Dynamic Label Generator object.
		 */
		virtual std::unique_ptr<IDynamicLabelGenerator> CreateDynamicLabel(std::unique_ptr<IDynamicLabel> &bindingObjPtr) = 0;
	};
}