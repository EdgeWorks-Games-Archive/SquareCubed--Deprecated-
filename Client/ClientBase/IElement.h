#pragma once

// Hides a warning coming from a VC++ Bug
#pragma warning( disable : 4250 )

#include <glm/glm.hpp>

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
	public: // Initialization/Uninitialization
		IElementGenerator() :
			PositionType(GUI::PositionType::Auto),
			Position(0, 0),
			HorizontalPos(GUI::HorizontalAlign::Left),
			VerticalPos(GUI::VerticalAlign::Top)
		{}
		virtual ~IElementGenerator() {}

	public: // Properties
		// Position Data
		GUI::PositionType PositionType;
		glm::ivec2 Position;
		GUI::HorizontalAlign HorizontalPos;
		GUI::VerticalAlign VerticalPos;

	public: // Generation
		/** Generates the element into the output stream and generates a the binding element object if needed.
		 * \param[out] output Target output stream.
		 */
		virtual void Generate(std::ostream &output) = 0;
	};
}