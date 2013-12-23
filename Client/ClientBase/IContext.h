#pragma once

#include "InputData.h"

namespace Context {
	class IWindow;

	/// <summary>
	/// Implementations of IContext are responsible for providing an IWindow
	/// object as well as capturing events and input from the operating system.
	/// </summary>
	class IContext {
	public: // Initialization/Uninitialization
		virtual ~IContext() {}

	public: // Property Accessors
		/// <summary>Gets the Main Window</summary>
		/// <returns>Reference to the Main Window</returns>
		virtual IWindow& GetMainWindow() = 0;

	public: // Input Handling
		virtual Input::KeyID GetKeyId(unsigned char key) = 0;
		virtual const Input::SpecialKeyIDs& GetSpecialKeyIds() = 0;

	public: // Game Loop
		/// <summary>Polls Events and Execute Event Handlers</summary>
		virtual void PollEvents() = 0;
	};
}