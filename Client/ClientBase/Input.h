#pragma once

#include "InputData.h"

#include <CommonLib/Events.h>

namespace Context { class IContext; }

namespace Input {
	// Generic Data //

	enum class MouseButton { None, Left, Right, Middle };

	struct CursorPosition {
		glm::vec2 Absolute;
		glm::vec2 World; // < !Not implemented!
	};

	// Event Structs //

	struct KeyChangeEventArgs final {
		KeyID KeyId;
		bool Down;
		bool ShiftMod;
	};

	struct CharInputEventArgs final {
		unsigned int Char;
	};

	struct MouseEventArgs final {
		CursorPosition CursorPosition;
		MouseButton MouseButton;
		bool IsPressed;

		// Modifiers
		bool IsLeftButtonDown, IsRightButtonDown, IsMiddleButtonDown;
	};

	class Input final {
		Context::IContext &m_Context;

	public: // Initialization/Uninitialization
		Input(Context::IContext &context);
		~Input();

	public: // Events
		Utils::Event<KeyChangeEventArgs> OnKeyChange;
		Utils::Event<CharInputEventArgs> OnCharInput;
		Utils::Event<MouseEventArgs> OnCursorPosChange;
		Utils::Event<MouseEventArgs> OnMouseButtonChange;

	private: // Stored Key Bindings
		KeyID m_ForwardKey;
		KeyID m_BackwardKey;
		KeyID m_LeftKey;
		KeyID m_RightKey;

	public: // Key Accessors
		bool GetForwardKey();
		bool GetBackwardKey();
		bool GetLeftKey();
		bool GetRightKey();

	public: // Complex Input Accessors
		AxisDesc GetMovementAxis();

	public: // Mouse/Cursor Accessors
		const CursorPosition& GetCursorPosition();

	public: // Utilities
		Input::KeyID GetKeyId(unsigned char key);
		const SpecialKeyIDs& GetSpecialKeyIds();

	private: // Input Storing
		bool m_Keys[100];
		Input::MouseEventArgs m_LastMouse;

	private: // Key Callback
		void KeyCallback(int key, int scancode, int action, int mods);
		void CharCallback(unsigned int ch);
		void CursorPosCallback(double x, double y);
		void MouseButtonCallback(int button, int action, int mods);
	};
}