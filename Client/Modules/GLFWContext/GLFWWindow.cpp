#include "GLFWWindow.h"

#include <glfw/include/GLFW/glfw3.h>

namespace GLFWContext {
	// Static Callback Functions

	std::function<void(int, int, int, int)> GLFWWindow::sm_KeyCallbackFunc;
	std::function<void(unsigned int)> GLFWWindow::sm_CharCallbackFunc;
	std::function<void(double, double)> GLFWWindow::sm_CursorPosCallbackFunc;
	std::function<void(int, int, int)> GLFWWindow::sm_MouseButtonCallbackFunc;

	void GLFWWindow::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { sm_KeyCallbackFunc(key, scancode, action, mods); }
	void GLFWWindow::CharCallback(GLFWwindow* window, unsigned int ch) { sm_CharCallbackFunc(ch); }
	void GLFWWindow::CursorPosCallback(GLFWwindow* window, double x, double y) { sm_CursorPosCallbackFunc(x, y); }
	void GLFWWindow::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) { sm_MouseButtonCallbackFunc(button, action, mods); }

	// Initialization/Uninitialization

	GLFWWindow::GLFWWindow(int x, int y) {
		// Set Window Hints
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		glfwWindowHint(GLFW_SAMPLES, 4);
		
		// Create Window
		m_Window = glfwCreateWindow(
			x, y,
			"SquareCubed Client",
			NULL,
			NULL);
		if (!m_Window)
			throw std::exception("Failed to create window.");
	}

	GLFWWindow::~GLFWWindow() {
		glfwDestroyWindow(m_Window);
	}

	// Property Accessors

	bool GLFWWindow::HasCloseRequest() { return (glfwWindowShouldClose(m_Window) & 1); }

	// Utility Functions

	void GLFWWindow::MakeContexCurrent() { glfwMakeContextCurrent(m_Window); }
	void GLFWWindow::SwapBuffer() { glfwSwapBuffers(m_Window); }

	void GLFWWindow::SetKeyCallback(std::function<void(int, int, int, int)> callback) {
		sm_KeyCallbackFunc = callback;
		glfwSetKeyCallback(m_Window, KeyCallback);
	}

	void GLFWWindow::SetCharCallback(std::function<void(unsigned int)> callback) {
		sm_CharCallbackFunc = callback;
		glfwSetCharCallback(m_Window, CharCallback);
	}

	void GLFWWindow::SetCursorPosCallback(std::function<void(double, double)> callback) {
		sm_CursorPosCallbackFunc = callback;
		glfwSetCursorPosCallback(m_Window, CursorPosCallback);
	}

	void GLFWWindow::SetMouseButtonCallback(std::function<void(int, int, int)> callback) {
		sm_MouseButtonCallbackFunc = callback;
		glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
	}
}