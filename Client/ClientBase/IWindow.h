#pragma once

#include <functional>

namespace Context {
	class IWindow {
	public:
		virtual ~IWindow() {}

	public: // Property Accessors
		/// <summary>Determines whether the window has a close request.</summary>
		/// <returns>True if it has a close request.</returns>
		virtual bool HasCloseRequest() = 0;

	public: // Utility Functions
		/// <summary>Swaps the back buffer.</summary>
		virtual void SwapBuffer() = 0;

		/// <summary>Sets the key callback.</summary>
		/// <param name="callback">The callback function.</param>
		virtual void SetKeyCallback(std::function<void(int, int, int, int)> callback) = 0;

		virtual void SetCharCallback(std::function<void(unsigned int)> callback) = 0;

		virtual void SetCursorPosCallback(std::function<void(double, double)> callback) = 0;

		virtual void SetMouseButtonCallback(std::function<void(int, int, int)> callback) = 0;
	};
}