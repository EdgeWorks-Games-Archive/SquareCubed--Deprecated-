#pragma once

#include <ClientBase/IContext.h>
#include <ClientBase/Input.h>

#include <memory>

namespace GLFWContext {
	class GLFWWindow;

	class GLFWContext final : public Context::IContext {
	public: // Initialization/Uninitialization
		GLFWContext();
		~GLFWContext();

	private: // Properties
		std::unique_ptr<GLFWWindow> m_Window;
		Input::SpecialKeyIDs m_SpecialKeyIds;

	public: // Property Accessors
		Context::IWindow& GetMainWindow();

	public: // Input Handling
		Input::KeyID GetKeyId(unsigned char key);
		const Input::SpecialKeyIDs& GetSpecialKeyIds();

	public: // Game Loop
		void PollEvents();
	};
}