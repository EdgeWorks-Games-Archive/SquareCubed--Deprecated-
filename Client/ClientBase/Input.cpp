#include "Input.h"

#include <ClientBase/IContext.h>
#include <ClientBase/IWindow.h>
#include <ClientBase/IGraphics.h>
#include <ClientBase/ICamera.h>

namespace Input {
	// Key Accessors

	bool Input::GetForwardKey() { return m_Keys[m_ForwardKey]; }
	bool Input::GetBackwardKey() { return m_Keys[m_BackwardKey]; }
	bool Input::GetLeftKey() { return m_Keys[m_LeftKey]; }
	bool Input::GetRightKey() { return m_Keys[m_RightKey]; }

	// Complex Input Accessors

	AxisDesc Input::GetMovementAxis() {
		// Get Raw Values from Keys
		AxisDesc retVal;
		if (GetRightKey())
			retVal.RawValues.x += 1;
		if (GetLeftKey())
			retVal.RawValues.x -= 1;
		if (GetForwardKey())
			retVal.RawValues.y += 1;
		if (GetBackwardKey())
			retVal.RawValues.y -= 1;

		// Check if there was some input
		if (retVal.RawValues.x != 0 || retVal.RawValues.y != 0) {
			// Hurray, Input! Make sure the caller knows
			retVal.Any = true;

			// Calculate Angle
			Anglef angle = atan2f(retVal.RawValues.x, retVal.RawValues.y);

			// Scale Input
			retVal.Scaled.x = angle.GetSin() * fabs(retVal.RawValues.x);
			retVal.Scaled.y = angle.GetCos() * fabs(retVal.RawValues.y);

			// And Set the Angle
			retVal.Angle.Radians = -angle.Radians;
		}

		return retVal;
	}

	KeyMods& Input::GetKeyMods() { return m_KeyMods; }

	// Mouse/Cursor Accessors

	const CursorPosition& Input::GetCursorPosition() { return m_LastMouse.CursorPosition; }

	// Utilities

	KeyID Input::GetKeyId(unsigned char key) { return m_Context.GetKeyId(key); }
	const SpecialKeyIDs& Input::GetSpecialKeyIds() { return m_Context.GetSpecialKeyIds(); }

	// Initialization/Uninitialization

	Input::Input(Context::IContext &context, Graphics::IGraphics &graphics) :
		m_Context(context),
		m_Graphics(graphics),

		m_ForwardKey(m_Context.GetKeyId('W')),
		m_BackwardKey(m_Context.GetKeyId('S')),
		m_LeftKey(m_Context.GetKeyId('A')),
		m_RightKey(m_Context.GetKeyId('D')),
#pragma warning( disable : 4351 ) // New behavior warning
		m_Keys()
	{
		// Bind Key Callback
		m_Context.GetMainWindow().SetKeyCallback(std::bind(
			&Input::KeyCallback,
			this,
			std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3,
			std::placeholders::_4));

		// Bind Char Callback
		m_Context.GetMainWindow().SetCharCallback(std::bind(
			&Input::CharCallback,
			this,
			std::placeholders::_1));

		// Bind Cursor Pos Callback
		m_Context.GetMainWindow().SetCursorPosCallback(std::bind(
			&Input::CursorPosCallback,
			this,
			std::placeholders::_1,
			std::placeholders::_2));

		// Bind Mouse Button Callback
		m_Context.GetMainWindow().SetMouseButtonCallback(std::bind(
			&Input::MouseButtonCallback,
			this,
			std::placeholders::_1,
			std::placeholders::_2,
			std::placeholders::_3));

		// Log Initialization
		//m_Logger.LogInfo("Input Initialized");
	}

	Input::~Input() {
	}

	// Key Callback

	void Input::KeyCallback(int key, int scancode, int action, int mods) {
		// Filter out Special Keys
		if (key < 100) {
			// Set key in array
			if (action == 0)
				m_Keys[key] = false;
			else if (action == 1)
				m_Keys[key] = true;
		}

		// Set Key Mods (right now hardcoded values)
		else if (key == 257) // Shift
			m_KeyMods.Shift = !(action == 0);
		else if (key == 341) // Left Control
			m_KeyMods.Control = !(action == 0);

		// Invoke Event
		KeyChangeEventArgs evtArgs;
		evtArgs.KeyId = key;
		// action can be numbers other then 1 or 0
		evtArgs.Down = !(action == 0);
		evtArgs.Repeat = action == 2;
		evtArgs.ShiftMod = false;
		OnKeyChange.Invoke(evtArgs);
	}

	void Input::CharCallback(unsigned int ch) {
		// Invoke Event
		CharInputEventArgs evtArgs;
		evtArgs.Char = std::move(ch);
		OnCharInput.Invoke(evtArgs);
	}

	void Input::CursorPosCallback(double x, double y) {
		// Invoke Event
		m_LastMouse.CursorPosition.Absolute.x = (float)x;
		m_LastMouse.CursorPosition.Absolute.y = (float)y;
		// Might need to update immediately? Not sure, let's not.
		//m_LastMouse.CursorPosition.World = m_Graphics.GetMainCamera().ResolveWorldPosition(m_LastMouse.CursorPosition.Absolute);
		OnCursorPosChange.Invoke(m_LastMouse);
	}

	void Input::MouseButtonCallback(int button, int action, int mods) {
		bool pressed = (action == 1);

		// Set Mouse Button
		if (button == 0) {
			m_LastMouse.MouseButton = MouseButton::Left;
			m_LastMouse.IsLeftButtonDown = pressed;
		}
		else if (button == 1) {
			m_LastMouse.MouseButton = MouseButton::Right;
			m_LastMouse.IsRightButtonDown = pressed;
		}
		else if (button == 2) {
			m_LastMouse.MouseButton = MouseButton::Middle;
			m_LastMouse.IsMiddleButtonDown = pressed;
		}
		m_LastMouse.IsPressed = pressed;

		// Invoke Event
		OnMouseButtonChange.Invoke(m_LastMouse);
	}

	// Game Loop

	void Input::Update() {
		m_LastMouse.CursorPosition.World = m_Graphics.GetMainCamera().ResolveWorldPosition(m_LastMouse.CursorPosition.Absolute);
	}
}