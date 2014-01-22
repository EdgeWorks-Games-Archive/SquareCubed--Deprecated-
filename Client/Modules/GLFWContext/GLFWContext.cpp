#include "GLFWContext.h"
#include "GLFWContextLoader.h"

#include "GLFWWindow.h"

#include <glfw/include/GLFW/glfw3.h>

namespace GLFWContext {
	// Factory to avoid including the big compiler-grinding-to-a-crawl file
	Context::IContext* LoadContext() { return new GLFWContext(); }

	// Initialization/Uninitialization

	GLFWContext::GLFWContext() :
		m_Window(),
		m_SpecialKeyIds()
	{
		// Initialize GLFW
		if (!glfwInit())
			throw std::exception("GLFW failed to initialize.");

		// Create Window
		m_Window = std::unique_ptr<GLFWWindow>(new GLFWWindow(1024, 768));
		
		// Set OpenGL Context
		m_Window->MakeContexCurrent();

		// Set Special Keys
		m_SpecialKeyIds.Back = GLFW_KEY_BACKSPACE;
		m_SpecialKeyIds.Tab = GLFW_KEY_TAB;
		m_SpecialKeyIds.Enter = GLFW_KEY_ENTER;
		m_SpecialKeyIds.Delete = GLFW_KEY_DELETE;

		m_SpecialKeyIds.Up = GLFW_KEY_UP;
		m_SpecialKeyIds.Down = GLFW_KEY_DOWN;
		m_SpecialKeyIds.Left = GLFW_KEY_LEFT;
		m_SpecialKeyIds.Right = GLFW_KEY_RIGHT;
	}

	GLFWContext::~GLFWContext() {
		// This has to be done before glfwTerminate
		m_Window.reset();

		glfwTerminate();
	}

	// Property Accessors

	Context::IWindow& GLFWContext::GetMainWindow() { return *m_Window; }

	// Input Handling

	Input::KeyID GLFWContext::GetKeyId(unsigned char key) {
		// Make sure it's lowercase if alpha
		if (key >= 'A' && key <= 'Z')
			key += ('a' - 'A');

		if (key >= 'a' && key <= 'z') {
			// Resolve alpha key
			static const int diff = GLFW_KEY_A - 'a';
			return key + diff;
		}
		else if (key >= '0' && key <= '9') {
			// Resolve numeric key
			static const int diff = GLFW_KEY_0 - '0';
			return key + diff;
		}
		else if (key == ' ')
			return GLFW_KEY_SPACE;
		else if (key == '\n')
			return GLFW_KEY_ENTER;
		else if (key == '`')
			return GLFW_KEY_GRAVE_ACCENT;
		else
			throw std::exception("Cannot resolve invalid key character.");
	}

	const Input::SpecialKeyIDs& GLFWContext::GetSpecialKeyIds() {
		return m_SpecialKeyIds;
	}

	// Game Loop

	void GLFWContext::PollEvents() {
		glfwPollEvents();
	}
}