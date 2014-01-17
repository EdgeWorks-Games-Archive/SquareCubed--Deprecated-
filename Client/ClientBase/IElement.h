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

		class IElement {
		public:
			virtual ~IElement() {}
		};

		class IElementGenerator {
		public: // Initialization/Uninitialization
			IElementGenerator() :
				PositionType(PositionType::Auto),
				Position(0, 0),
				HorizontalPos(HorizontalAlign::Left),
				VerticalPos(VerticalAlign::Top)
			{}
			virtual ~IElementGenerator() {}

		public: // Properties
			// Position Data
			PositionType PositionType;
			glm::ivec2 Position;
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