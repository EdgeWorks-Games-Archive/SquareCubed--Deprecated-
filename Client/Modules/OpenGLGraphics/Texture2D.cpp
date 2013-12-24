#include "Texture2D.h"

#include "GLheaders.h"
#include "ILheaders.h"

namespace OpenGLGraphics {
	const char* Texture2D::GetType() { return "Texture2D"; }

	// Initialization/Uninitialization

	Texture2D::Texture2D(const std::string &path) :
		m_Size(),
		m_TextureID(0)
	{
		// Generate and Bind Image
		unsigned int imgID = 0;
		ilGenImages(1, &imgID);
		ilBindImage(imgID);

		// Load Image from File
		ILboolean success = ilLoadImage(path.c_str());
		if (!success) {
			std::string msg = "Unable to load image: ";
			msg += path;
			throw std::exception(msg.c_str());
		}

		// Convert Image to RGBA
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		if (!success) {
			std::string msg = "Unable to convert image to RGBA: ";
			msg += path;
			throw std::exception(msg.c_str());
		}

		// Create Texture from File Pixels
		LoadTextureFromPixels32(
			(unsigned int*) ilGetData(),
			glm::ivec2(
				(unsigned int) ilGetInteger(IL_IMAGE_WIDTH),
				(unsigned int) ilGetInteger(IL_IMAGE_HEIGHT)
			)
		);

		// Delete File from Memory
		ilDeleteImages(1, &imgID);
	}

	Texture2D::~Texture2D() {
		// Delete Texture if it Exists
		if (m_TextureID != 0)
			glDeleteTextures(1, &m_TextureID);
	}

	// Internal Utility Functions

	void Texture2D::LoadTextureFromPixels32(unsigned int* pixels, glm::ivec2 size) {
		// Generate and Bind Texture ID
		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		// Generate Texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

		// Set Texture Parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Unbind Texture
		glBindTexture(GL_TEXTURE_2D, NULL);
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			std::string exMsg = "Error loading texture from pixels: ";
			exMsg += (char*) gluErrorString(error);
			throw std::exception(exMsg.c_str());
		}

		// Set Texture Dimensions
		m_Size = std::move(size);
	}

	// Render Functions

	void Texture2D::Render(float x, float y, float w, float h) {
		if (m_TextureID != 0) {
			// Bind Texture
			glBindTexture(GL_TEXTURE_2D, m_TextureID);

			// Render Quad with Texture
			glBegin(GL_QUADS);
			glTexCoord2f(0.f, 1.f); glVertex2f(x, y);
			glTexCoord2f(1.f, 1.f); glVertex2f(x + w, y);
			glTexCoord2f(1.f, 0.f); glVertex2f(x + w, y + h);
			glTexCoord2f(0.f, 0.f); glVertex2f(x, y + h);
			glEnd();
		}
		else
			throw std::exception("Error rendering Graphics::Texture2D, no texture loaded.");
	}
}