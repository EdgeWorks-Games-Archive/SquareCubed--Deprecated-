#pragma once

#include "Renderer.h"
#include "ViewEventListener.h"
#include "SystemEventListener.h"
#include "GUIBindings.h"
#include "LogHandler.h"

#include <ClientBase/IGUI.h>
#include <ClientBase/Input.h>

#include <CommonLib/Events.h>

namespace Context { class IContext; }

namespace Utils { class ILoggingManager; }

namespace CoherentUIOpenGLUI {
	class CoherentUIOpenGLUI final : public GUI::IGUI {
		Input::Input &m_Input;

		// Helper Classes
		Renderer m_Renderer;

		// Event Listeners
		ViewEventListener m_ViewListener;
		SystemEventListener m_SystemListener;

		// Coherent UI Classes
		Coherent::UI::SystemSettings m_Settings;
		Coherent::UI::UISystem* m_System;

		// Bindings
		GUIBindings m_Bindings;

		// Logging
		LogHandler m_LogHandler;

		// OpenGL Stuff
		GLuint m_ProgramID;
		GLuint m_TextureID;
		GLuint m_TextureSamplerID;
		GLuint m_VertexBuffer;

	public: // Initialization/Uninitialization
		CoherentUIOpenGLUI(Utils::ILoggingManager &logManager, Input::Input &input);

	private: // Input Data
		const Input::SpecialKeyIDs &m_KeyIDs;

	private: // Event Callbacks
		Utils::EventScope m_EventScope;
		void OnViewReady(const Utils::EmptyEventArgs &args);
		void OnKeyInput(const Input::KeyChangeEventArgs &args);
		void OnCharInput(const Input::CharInputEventArgs &args);
		void OnCursorPosChange(const Input::MouseEventArgs &args);
		void OnMouseButtonChange(const Input::MouseEventArgs &args);

	public: // Utility Functions
		void SwitchView(std::wstring view);
		GUI::IGUIBindings& GetBindings();

	public: // View Helpers
		std::unique_ptr<GUI::IViewGenerator> CreateViewGenerator();
		void SwitchView(GUI::IView &view);

	public: // Game Loop
		void Update();
		void Render();
	};
}