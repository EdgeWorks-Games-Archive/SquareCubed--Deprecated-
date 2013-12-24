#include "OpenGLGraphics.h"
#include "OpenGLGraphicsLoader.h"

#include <ClientBase/IWindow.h>

#include "GLheaders.h"
#include "ILheaders.h"

namespace OpenGLGraphics {
	// Factory to avoid including the big compiler-grinding-to-a-crawl file
	Graphics::IGraphics* LoadGraphics(Context::IWindow &window, Content::Content &content) { return new OpenGLGraphics(window, content); }

	OpenGLGraphics::OpenGLGraphics(Context::IWindow &window, Content::Content &content) :
		m_Window(window),
		m_Factory(content),
		m_MainCamera(glm::ivec2(1024, 768))
	{
		// Default Camera Size
		m_MainCamera.SetHeight(10);

		// OpenGL Settings
		glEnable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_MULTISAMPLE);

		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_LINE_STIPPLE); // < has been deprecated, might not work on all targets

		// Activate Alpha Blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

		GLenum glError = glGetError();
		if (glError != GL_NO_ERROR) {
			std::string msg = "Error initializing OpenGL: ";
			msg += (char*) gluErrorString(glError);
			throw std::exception(msg.c_str());
		}

		// Initialize GLEW
		glewExperimental = GL_TRUE; // This is needed on some systems, or otherwise glGenVertexArrays may crash
		GLenum glewError = glewInit();
		if (glewError != GLEW_NO_ERROR) {
			std::string msg = "Error initializing GLEW: ";
			msg += (char*) glewGetErrorString(glewError);
			throw std::exception(msg.c_str());
		}

		// Initialize DevIL
		ilInit();
		ilClearColour(255, 255, 255, 000);
		ILenum ilError = ilGetError();
		if (ilError != IL_NO_ERROR) {
			std::string msg = "Error initializing DevIL: ";
			msg += iluErrorString(ilError);
			throw std::exception(msg.c_str());
		}
	}

	OpenGLGraphics::~OpenGLGraphics() {
	}

	// Property Accessors

	Graphics::ICamera& OpenGLGraphics::GetMainCamera() { return m_MainCamera; }

	// Utility Functions

	Graphics::IGraphicsFactory& OpenGLGraphics::GetFactory() { return m_Factory; }

	void OpenGLGraphics::Push() { glPushMatrix(); }
	void OpenGLGraphics::Pop() { glPopMatrix(); }
	void OpenGLGraphics::Translate(double x, double y) { glTranslated(x, y, 0); }
	void OpenGLGraphics::TranslateLayer(double z) { glTranslated(0, 0, z); }
	void OpenGLGraphics::Rotate(float rot) { glRotated(rot, 0, 0, 1); }
	void OpenGLGraphics::Flush() { glFinish(); }

	void OpenGLGraphics::RenderTest() {
		// Render Quad
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.0f);
		glEnd();
	}

	// Game Loop

	void OpenGLGraphics::BeginRender() {
		// Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Set the Projection Matrix based on the Main Camera
		glm::vec2 size = m_MainCamera.GetSize();
		glOrtho(
			-(size.x * 0.5f),
			size.x * 0.5f,
			-(size.y * 0.5f),
			size.y * 0.5f,
			0.0, 10.0); // Make sure everything behind the cam clips away
		// Note: zFar goes in the negative z direction

		// Translate and Rotate the Camera
		glm::vec3 rot = m_MainCamera.GetRotation();
		glRotated(-rot.x, 1, 0, 0);
		glRotated(-rot.y, 0, 1, 0);
		glRotated(-rot.z, 0, 0, 1);
		glm::vec3 pos = m_MainCamera.GetPosition();
		glTranslated(-pos.x, -pos.y, -pos.z);

		// Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Clear the Buffer
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLGraphics::BeginGUIRender() {
		// Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void OpenGLGraphics::EndRender() {
		m_Window.SwapBuffer();
	}
}