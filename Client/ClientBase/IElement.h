#pragma once

// Hides a warning coming from a VC++ Bug
#pragma warning( disable : 4250 )

#include <glm/glm.hpp>

#include <ostream>
#include <memory>

namespace GUI {
	namespace Elements {
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

		/** Color override types.
		 * Doesn't translate to exact colors, elements can
		 * decide what specific color value they translate to.
		 */
		enum class ColorType {
			/** No color override. */
			None,
			Red,
			Blue,
			Yellow
		};

		class IElement {
		public:
			virtual ~IElement() {}
		};

		class IElementGenerator {
		public: // Initialization/Uninitialization
			IElementGenerator() :
				Position(0, 0),
				PositionType(PositionType::Auto),
				HorizontalPos(HorizontalAlign::Left),
				VerticalPos(VerticalAlign::Top)
			{}
			virtual ~IElementGenerator() {}

		public: // Properties
			// Position Data
			glm::ivec2 Position;
			PositionType PositionType;
			HorizontalAlign HorizontalPos;
			VerticalAlign VerticalPos;

		public: // Generation
			/** Generates the element into the output stream and generates a the binding element object if needed.
			 * \param[out] output Target output stream.
			 */
			virtual void Generate(std::ostream &output) = 0;
		};

		class IElementContainer {
		public: // Adding Subcomponents
			virtual void Add(std::unique_ptr<IElementGenerator> element) = 0;
		};
	}
}