#pragma once

// Hides a warning coming from a VC++ Bug
#pragma warning( disable : 4250 )

#include <ostream>

namespace GUI {
	enum class PositionType {
		/** Automatically set position. */
		Auto,
		/** Place in a position relative to the parenting object. */
		Relative,
		/** Place in a position relative to the game window. */
		Absolute
	};

	enum class HorizontalAlign { Left, Right };
	enum class VerticalAlign { Top, Bottom };

	class IElement {
	public:
		virtual ~IElement() {}
	};

	class IElementGenerator {
	public:
		virtual ~IElementGenerator() {}

		/** Generates the element into the target file and generates a the binding element object.
		 * \param[out] file Target File.
		 */
		virtual void Generate(std::ostream &output) = 0;
	};
}