#pragma once

#include <CommonLib/postypes.h>

#include <glm/glm.hpp>

namespace Input {
	typedef unsigned int KeyID;

	struct AxisDesc final {
		glm::vec2 RawValues;

		// Useful Input Values
		bool Any;
		glm::vec2 Scaled;
		Anglef Angle;

		AxisDesc() :
			RawValues(),
			Any(),
			Scaled(),
			Angle()
		{}
	};

	/** Struct containing KeyIDs of special keys on the keyboard.
	 * Used by systems that need to translate input into another
	 * external library's input format.
	 * If you just need to get input from keys for ingame systems,
	 * you will never need these, use the getter functions in the
	 * Input class instead.
	 * \sa Input::Input
	 */
	struct SpecialKeyIDs final {
		KeyID Back, Tab, Enter, Delete;
		KeyID Up, Down, Left, Right;
	};
}