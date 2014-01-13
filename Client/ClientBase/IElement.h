#pragma once

#include <fstream>

namespace GUI {
	class IElement {
	};

	class IElementGenerator {
	public:
		/** Generates the element into the target file and generates a the binding element object.
		 * \param[out] file Target File.
		 */
		virtual void Generate(std::ofstream &file) = 0;
	};
}