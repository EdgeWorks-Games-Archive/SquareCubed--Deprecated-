#pragma once

#include "Types.h"

#include <memory>

namespace GUI {
	class IElementFactory {
	public:
		virtual ~IElementFactory() {}

		virtual std::unique_ptr<ILabelGenerator> CreateLabel() = 0;

		/** Creates a new Dynamic Label Generator.
		 * \param[in,out] bindingObjPtr Pointer that the binding object will be assigned to.
		 * \return A new Dynamic Label Generator object.
		 */
		virtual std::unique_ptr<IDynamicLabelGenerator> CreateDynamicLabel(std::unique_ptr<IDynamicLabel> &bindingObjPtr) = 0;

		virtual std::unique_ptr<IPanelGenerator> CreatePanel() = 0;
	};
}