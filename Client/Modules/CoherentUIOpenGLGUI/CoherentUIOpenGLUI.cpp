#include "CoherentUIOpenGLUI.h"
#include "CoherentUIOpenGLUILoader.h"

#include "View.h"

#include <ClientBase/IGUI.h>
#include <ClientBase/Input.h>
#include <ClientBase/IContext.h>

#include <Coherent/UI/License.h>
#include <Coherent/UI/InputEvents.h>
#include <Coherent/UI/View.h>

#include <sstream>

#define CUI_KEY_BACK 0x08
#define CUI_KEY_TAB 0x09
#define CUI_KEY_ENTER 0x0D
#define CUI_KEY_DELETE 0x2E

#define CUI_KEY_LEFT 0x25
#define CUI_KEY_UP 0x26
#define CUI_KEY_RIGHT 0x27
#define CUI_KEY_DOWN 0x28

#define CUI_KEY_A 'A'

namespace CoherentUIOpenGLUI {
	// Factory to avoid including the big compiler-grinding-to-a-crawl file
	GUI::IGUI* LoadGUI(Utils::ILoggingManager &logManager, Input::Input &input) { return new CoherentUIOpenGLUI(logManager, input); }

	// Initialization/Uninitialization

	CoherentUIOpenGLUI::CoherentUIOpenGLUI(Utils::ILoggingManager &logManager, Input::Input &input) :
		m_Input(input),

		m_Renderer(),

		m_ViewListener(m_Renderer),
		m_SystemListener(m_ViewListener),

		m_Bindings(m_ViewListener),
		m_ElementFactory(m_ViewListener),

		m_LogHandler(logManager),

		m_Settings(),
		m_System(nullptr),

		m_KeyIDs(input.GetSpecialKeyIds())
	{
		// Attach View Event
		m_ViewListener.OnViewReady.AttachMember(this, &CoherentUIOpenGLUI::OnViewReady, m_EventScope);

		// Initialize System
		m_Settings.HostDirectory = L"Host";
#ifdef _DEBUG
		m_Settings.DebuggerPort = 1234;
#endif
		m_System = InitializeUISystem(COHERENT_KEY, m_Settings, &m_SystemListener, Coherent::Logging::Info, &m_LogHandler);
		if (!m_System)
			throw std::exception("Coherent UI failed to initialize!");

		// This is completely safe, because no callback will be called outside Update()
		m_SystemListener.SetSystem(m_System);

		// Create and compile our GLSL program from the shaders
		m_ProgramID = m_Renderer.CreateShaderProgram(
			"Content/Shaders/CoherentUI.vert",
			"Content/Shaders/CoherentUI.frag"
		);

		// Load the initial texture. The texture ID returned is saved internally by the renderer
		// and can be obtained by the Renderer::GetTextureID method. This texture ID is later
		// used by the ViewEventListener to change the image data of the texture with the
		// bytes received from Coherent UI.
		m_TextureID = m_Renderer.CreateTexture(1024, 768);

		// Get a handle for the texture sampler uniform
		m_TextureSamplerID = glGetUniformLocation(m_ProgramID, "textureSampler");

		float vertexData [] =
		{
			// -- position --     -- uv --
			-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			3.0f, -1.0f, 0.0f, 2.0f, 1.0f,
			-1.0f, 3.0f, 0.0f, 0.0f, -1.0f
		};

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	}

	// Event Callbacks

	void CoherentUIOpenGLUI::OnViewReady(const Utils::EmptyEventArgs &args) {
		// Attach input event
		m_Input.OnKeyChange.AttachMember(this, &CoherentUIOpenGLUI::OnKeyInput, m_EventScope);
		m_Input.OnCharInput.AttachMember(this, &CoherentUIOpenGLUI::OnCharInput, m_EventScope);
		m_Input.OnCursorPosChange.AttachMember(this, &CoherentUIOpenGLUI::OnCursorPosChange, m_EventScope);
		m_Input.OnMouseButtonChange.AttachMember(this, &CoherentUIOpenGLUI::OnMouseButtonChange, m_EventScope);
	}

	void CoherentUIOpenGLUI::OnKeyInput(const Input::KeyChangeEventArgs &args) {
		Coherent::UI::KeyEventData keyData;
		keyData.KeyCode = -1;

		// Resolve key
		if (args.KeyId == m_KeyIDs.Back)
			keyData.KeyCode = CUI_KEY_BACK;
		else if (args.KeyId == m_KeyIDs.Tab)
			keyData.KeyCode = CUI_KEY_TAB;
		else if (args.KeyId == m_KeyIDs.Enter)
			keyData.KeyCode = CUI_KEY_ENTER;
		else if (args.KeyId == m_KeyIDs.Delete)
			keyData.KeyCode = CUI_KEY_DELETE;

		else if (args.KeyId == m_KeyIDs.Up)
			keyData.KeyCode = CUI_KEY_UP;
		else if (args.KeyId == m_KeyIDs.Down)
			keyData.KeyCode = CUI_KEY_DOWN;
		else if (args.KeyId == m_KeyIDs.Left)
			keyData.KeyCode = CUI_KEY_LEFT;
		else if (args.KeyId == m_KeyIDs.Right)
			keyData.KeyCode = CUI_KEY_RIGHT;

		// Make sure we got a valid key
		if (keyData.KeyCode != -1) {
			if (args.Down)
				keyData.Type = Coherent::UI::KeyEventData::KeyDown;
			else
				keyData.Type = Coherent::UI::KeyEventData::KeyUp;

			// Notify Coherent UI of key change
			m_ViewListener.GetView().KeyEvent(keyData);
		}
	}

	void CoherentUIOpenGLUI::OnCharInput(const Input::CharInputEventArgs &args) {
		Coherent::UI::KeyEventData keyData;

		// Set Coherent UI key data
		keyData.KeyCode = args.Char;
		keyData.Type = Coherent::UI::KeyEventData::Char;

		// Notify Coherent UI of key change
		m_ViewListener.GetView().KeyEvent(keyData);
	}

	void CoherentUIOpenGLUI::OnCursorPosChange(const Input::MouseEventArgs &args) {
		Coherent::UI::MouseEventData mouseData;

		mouseData.X = (int) args.CursorPosition.Absolute.x;
		mouseData.Y = (int) args.CursorPosition.Absolute.y;

		if (args.MouseButton == Input::MouseButton::None)
			mouseData.Button = Coherent::UI::MouseEventData::ButtonNone;
		else if (args.MouseButton == Input::MouseButton::Left)
			mouseData.Button = Coherent::UI::MouseEventData::ButtonLeft;
		else if (args.MouseButton == Input::MouseButton::Right)
			mouseData.Button = Coherent::UI::MouseEventData::ButtonRight;
		else if (args.MouseButton == Input::MouseButton::Middle)
			mouseData.Button = Coherent::UI::MouseEventData::ButtonMiddle;

		mouseData.Type = Coherent::UI::MouseEventData::MouseMove;

		mouseData.MouseModifiers.IsLeftButtonDown = args.IsLeftButtonDown;
		mouseData.MouseModifiers.IsRightButtonDown = args.IsRightButtonDown;
		mouseData.MouseModifiers.IsMiddleButtonDown = args.IsMiddleButtonDown;

		// Notify Coherent UI of mouse change
		m_ViewListener.GetView().MouseEvent(mouseData);
	}

	void CoherentUIOpenGLUI::OnMouseButtonChange(const Input::MouseEventArgs &args) {
		Coherent::UI::MouseEventData mouseData;

		mouseData.X = (int) args.CursorPosition.Absolute.x;
		mouseData.Y = (int) args.CursorPosition.Absolute.y;

		if (args.MouseButton == Input::MouseButton::None)
			mouseData.Button = Coherent::UI::MouseEventData::ButtonNone;
		else if (args.MouseButton == Input::MouseButton::Left)
			mouseData.Button = Coherent::UI::MouseEventData::ButtonLeft;
		else if (args.MouseButton == Input::MouseButton::Right)
			mouseData.Button = Coherent::UI::MouseEventData::ButtonRight;
		else if (args.MouseButton == Input::MouseButton::Middle)
			mouseData.Button = Coherent::UI::MouseEventData::ButtonMiddle;

		if (args.IsPressed)
			mouseData.Type = Coherent::UI::MouseEventData::MouseDown;
		else
			mouseData.Type = Coherent::UI::MouseEventData::MouseUp;

		mouseData.MouseModifiers.IsLeftButtonDown = args.IsLeftButtonDown;
		mouseData.MouseModifiers.IsRightButtonDown = args.IsRightButtonDown;
		mouseData.MouseModifiers.IsMiddleButtonDown = args.IsMiddleButtonDown;

		// Notify Coherent UI of mouse change
		m_ViewListener.GetView().MouseEvent(mouseData);
	}

	// Utility Functions

	void CoherentUIOpenGLUI::SwitchView(std::wstring view) {
		// Set Info
		Coherent::UI::ViewInfo info;
		info.Width = 1024;
		info.Height = 768;
		info.UsesSharedMemory = true;
		info.IsTransparent = true;

		// Build View Path
		std::wstringstream ss;
		ss << L"coui://Content/GUI/Deprecated/Views/" << view << "/" << view << ".html";

		// Replace View and Unhook Events if needed
		if (&m_ViewListener.GetView() != nullptr) {
			// Unhook Events
			m_Input.OnKeyChange.DetachForScope(m_EventScope);
			m_Input.OnCharInput.DetachForScope(m_EventScope);
			m_Input.OnCursorPosChange.DetachForScope(m_EventScope);
			m_Input.OnMouseButtonChange.DetachForScope(m_EventScope);

			// Destroy old View
			m_ViewListener.GetView().Destroy();
		}
		m_System->CreateView(info, ss.str().c_str(), &m_ViewListener);
	}

	void CoherentUIOpenGLUI::SwitchView(GUI::Elements::IView &view) {
		// Convert view to our own View
		View &ourView = static_cast<View&>(view);

		// Set Info
		Coherent::UI::ViewInfo info;
		info.Width = 1024;
		info.Height = 768;
		info.UsesSharedMemory = true;
		info.IsTransparent = true;

		// Build View Path
		std::wstringstream ss;
		ss << L"coui://" << ourView.GetPath();

		// Replace View and Unhook Events if needed
		if (&m_ViewListener.GetView() != nullptr) {
			// Unhook Events
			m_Input.OnKeyChange.DetachForScope(m_EventScope);
			m_Input.OnCharInput.DetachForScope(m_EventScope);
			m_Input.OnCursorPosChange.DetachForScope(m_EventScope);
			m_Input.OnMouseButtonChange.DetachForScope(m_EventScope);

			// Destroy old View
			m_ViewListener.GetView().Destroy();
		}
		m_System->CreateView(info, ss.str().c_str(), &m_ViewListener);
	}

	GUI::IGUIBindings& CoherentUIOpenGLUI::GetBindings() { return m_Bindings; }
	GUI::Elements::IElementFactory& CoherentUIOpenGLUI::GetElementFactory() { return m_ElementFactory; }

	// View Helpers

	std::unique_ptr<GUI::Elements::IViewGenerator> CoherentUIOpenGLUI::CreateViewGenerator() {
		return std::make_unique<ViewGenerator>(m_ViewListener);
	}

	// Game Loop

	void CoherentUIOpenGLUI::Update() {
		m_System->Update();
	}

	void CoherentUIOpenGLUI::Render() {
		// Fetch the Coherent UI Surfaces
		m_System->FetchSurfaces();

		// Use our shader
		glUseProgram(m_ProgramID);

		// Bind our texture to texture unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		// Set the texture sampler to use texture unit 0
		glUniform1i(m_TextureSamplerID, 0);

		// Vertices attribute buffer
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		// Position attribute pointer
		glVertexAttribPointer(
			0,                  // attribute location
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			5 * sizeof(float),  // stride
			(void*) 0            // array buffer offset
		);

		// UV attribute pointer
		glVertexAttribPointer(
			1,                  // attribute location
			2,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			5 * sizeof(float),  // stride
			(void*) (3 * sizeof(float)) // array buffer offset
		);

		// Draw the texture!
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Clean up
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glBindTexture(GL_TEXTURE_2D, 0);
		glUseProgram(0);
	}
}