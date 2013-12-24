#pragma once

#include "GLheaders.h"

/// Very simple renderer, capable of using a single shader program and a single texture
class Renderer
{
public:
	Renderer();
	~Renderer();

	GLuint CreateTexture(int width, int height, unsigned char* data = nullptr);
	GLuint CreateTextureFrom24BPPBitmap(const char* bitmap);
	GLuint CreateShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile);

	GLuint GetTextureID() const;
	GLuint GetShaderProgramID() const;

private:
	GLuint m_Texture;
	GLuint m_Program;
};