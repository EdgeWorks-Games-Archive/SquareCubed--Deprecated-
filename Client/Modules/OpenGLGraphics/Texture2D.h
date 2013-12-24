#pragma once

#include <ClientBase/ITexture2D.h>
#include <ClientBase/IContentBase.h>

#include <glm/glm.hpp>

#include <string>

namespace OpenGLGraphics {
	class Texture2D final : public Graphics::ITexture2D, public Content::IContentBase {
	public: static const char* GetType();

	public: // Initialization/Uninitialization
		Texture2D(const std::string &path);
		~Texture2D();

	private: // Properties
		glm::ivec2 m_Size;
		unsigned int m_TextureID;

	private: // Internal Utility Functions
		void LoadTextureFromPixels32(unsigned int* pixels, glm::ivec2 size);

	public: // Render Functions
		void Render(float x, float y, float w, float h);
	};
}