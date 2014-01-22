#include "Renderer.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>

Renderer::Renderer() :
	m_Texture(GL_INVALID_INDEX)
{}

Renderer::~Renderer()
{
}

GLuint Renderer::GetTextureID() const
{
	return m_Texture;
}

GLuint Renderer::GetShaderProgramID() const
{
	return m_Program;
}


GLuint Renderer::CreateTextureFrom24BPPBitmap(const char* bitmap)
{
	// Data read from the header of the BMP file
	static const unsigned int HEADER_SIZE = 54;
	unsigned char header[HEADER_SIZE];
	//unsigned int dataPos;
	unsigned int imageSize;
	unsigned int width;
	unsigned int height;

	// Open the file
	std::ifstream ifs(bitmap, std::ios::binary);
	if (!ifs.good())
	{
		return -1;
	}

	// Read the header
	ifs.read(reinterpret_cast<char*>(header), HEADER_SIZE);

	// A BMP files always begins with "BM"
	if (header[0] != 'B' || header[1] != 'M')
	{
		return -2;
	}

	// Make sure this is a 24bpp file
	if ((*(int*) &(header[0x1E]) != 0) || (*(int*) &(header[0x1C]) != 24))
	{
		return -3;
	}

	// Read the information about the image
	//dataPos = *(int*) &(header[0x0A]);
	imageSize = *(int*) &(header[0x22]);
	width = *(int*) &(header[0x12]);
	height = *(int*) &(header[0x16]);

	// If the BMP file is not well formatted, regenerate missing data
	if (imageSize == 0)
	{
		imageSize = width * height * 3; // 3, because we're reading only 24BPP bitmaps
	}
	/*if (dataPos == 0)
	{
		dataPos = HEADER_SIZE;
	}*/

	// Create a buffer and read the pixel data
	std::vector<unsigned char> rgbData(imageSize);

	ifs.read(reinterpret_cast<char*>(&rgbData[0]), imageSize);
	ifs.close();

	return CreateTexture(width, height, &rgbData[0]);
}

GLuint Renderer::CreateTexture(int width, int height, unsigned char* data)
{
	assert(m_Texture == GL_INVALID_INDEX);

	std::vector<unsigned char> blankImage;
	if (data == nullptr)
	{
		blankImage.resize(width * height * 4);
		std::fill(blankImage.begin(), blankImage.end(), (unsigned char) 0xFF);
		data = &blankImage[0];
	}

	// Create the OpenGL texture
	glGenTextures(1, &m_Texture);

	glBindTexture(GL_TEXTURE_2D, m_Texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);

	// Set bilinear filtering for the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	return m_Texture;
}


static std::string ReadWholeFile(const char* file)
{
	std::ifstream ifs(file);
	std::string contents;

	if (ifs.good())
	{
		ifs.seekg(0, std::ios::end);
		contents.reserve(std::string::size_type(ifs.tellg()));
		ifs.seekg(0, std::ios::beg);

		contents.assign((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	}

	return contents;
}

static void PrintError(const std::string& errorMsg)
{
	if (!errorMsg.empty())
	{
		fprintf(stderr, "%s\n", errorMsg.c_str());
	}
}

GLuint Renderer::CreateShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile)
{
	// Create the shaders
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string vertexShaderCode = ReadWholeFile(vertexShaderFile);

	// Read the Fragment Shader code from the file
	std::string fragmentShaderCode = ReadWholeFile(fragmentShaderFile);

	GLint result = GL_FALSE;
	int infoLogLength;

	// Compile Vertex Shader
	const char* vertexShaderCodePtr = vertexShaderCode.c_str();
	glShaderSource(vertexShaderID, 1, &vertexShaderCodePtr, nullptr);
	glCompileShader(vertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength)
	{
		std::string vertexShaderErrorMessage(infoLogLength, '\0');
		glGetShaderInfoLog(vertexShaderID, infoLogLength, nullptr, &vertexShaderErrorMessage[0]);
		PrintError(vertexShaderErrorMessage);
	}
	// Compile Fragment Shader
	const char* fragmentShaderCodePtr = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentShaderCodePtr, nullptr);
	glCompileShader(fragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength)
	{
		std::string fragmentShaderErrorMessage(infoLogLength, '\0');
		glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
		PrintError(fragmentShaderErrorMessage);
	}
	// Link the program
	m_Program = glCreateProgram();
	glAttachShader(m_Program, vertexShaderID);
	glAttachShader(m_Program, fragmentShaderID);
	glLinkProgram(m_Program);

	// Check the program
	glGetProgramiv(m_Program, GL_LINK_STATUS, &result);
	glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength)
	{
		std::string programErrorMessage(infoLogLength, '\0');
		glGetProgramInfoLog(m_Program, infoLogLength, NULL, &programErrorMessage[0]);
		PrintError(programErrorMessage);
	}
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return m_Program;
}

