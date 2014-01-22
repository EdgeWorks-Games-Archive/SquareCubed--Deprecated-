#pragma once

#include <ClientBase/IWindow.h>

// Front-Declare GLFW Stuff
struct GLFWwindow;

namespace GLFWContext {
	class GLFWWindow final : public Context::IWindow {
	private: // Static Callback Functions
		static std::function<void(int, int, int, int)> sm_KeyCallbackFunc;
		static std::function<void(unsigned int)> sm_CharCallbackFunc;
		static std::function<void(double, double)> sm_CursorPosCallbackFunc;
		static std::function<void(int, int, int)> sm_MouseButtonCallbackFunc;

		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void CharCallback(GLFWwindow* window, unsigned int ch);
		static void CursorPosCallback(GLFWwindow* window, double x, double y);
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	public: // Initialization/Uninitialization
		GLFWWindow(int x, int y);
		~GLFWWindow();

	private: // Properties
		GLFWwindow* m_Window;

	public: // Property Accessors
		bool HasCloseRequest();

	public: // Utility Functions
		void MakeContexCurrent();
		void SwapBuffer();

		void SetKeyCallback(std::function<void(int, int, int, int)> callback);
		void SetCharCallback(std::function<void(unsigned int)> callback);
		void SetCursorPosCallback(std::function<void(double, double)> callback);
		void SetMouseButtonCallback(std::function<void(int, int, int)> callback);
	};
}