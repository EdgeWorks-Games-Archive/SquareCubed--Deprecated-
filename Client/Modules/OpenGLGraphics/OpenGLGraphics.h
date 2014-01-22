#pragma once

#include "OpenGLGraphicsFactory.h"
#include "OpenGLCamera.h"

#include <ClientBase/IGraphics.h>

namespace Context { class IWindow; }

namespace OpenGLGraphics {
	class OpenGLGraphics final : public Graphics::IGraphics {
		Context::IWindow &m_Window;
		OpenGLGraphicsFactory m_Factory;

	public: // Initialization/Uninitialization
		OpenGLGraphics(Context::IWindow &window, Content::Content &content);
		~OpenGLGraphics();

	private: // Properties
		OpenGLCamera m_MainCamera;

	public: // Property Accessors
		Graphics::ICamera& GetMainCamera();

	public: // Utility Functions
		Graphics::IGraphicsFactory& GetFactory();

		void Push();
		void Pop();
		void Translate(double x, double y);
		void TranslateLayer(double z);
		void Rotate(float rot);
		void Flush();

		void RenderTest();

	public: // Game Loop
		void BeginRender();
		void BeginGUIRender();
		void EndRender();
	};
}