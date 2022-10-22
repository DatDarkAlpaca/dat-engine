#include "pch.h"
#include "ResourceManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void dat::ResourceManager::clear()
{
	for (auto it = m_Shaders.begin(); it != m_Shaders.end(); ++it)
	{
		glDeleteProgram(it->second.ID);
	}

	for (auto it = m_Textures.begin(); it != m_Textures.end(); ++it)
	{
		glDeleteTextures(1, &it->second.ID);
	}
}

dat::Shader dat::ResourceManager::loadShader(std::string_view shaderName, const char* vertexShaderFile, const char* fragmentShaderFile)
{
	m_Shaders[shaderName] = loadShaderFromFile(vertexShaderFile, fragmentShaderFile);
	return m_Shaders[shaderName];
}

dat::Shader dat::ResourceManager::getShader(std::string_view shaderName)
{
	return m_Shaders[shaderName];
}

dat::Texture2D dat::ResourceManager::loadTexture(std::string_view textureName, const char* textureFile, bool alpha)
{
	m_Textures[textureName] = loadTextureFromFile(textureFile, alpha);
	return m_Textures[textureName];
}

dat::Texture2D dat::ResourceManager::getTexture(std::string_view textureName)
{
	return m_Textures[textureName];
}

dat::Shader dat::ResourceManager::loadShaderFromFile(const char* vertexShaderFile, const char* fragmentShaderFile)
{
	std::string vertexCode, fragmentCode;

	try
	{
		std::ifstream vertexFile(vertexShaderFile);
		std::ifstream fragmentFile(fragmentShaderFile);

		std::stringstream vertexStream, fragmentStream;

		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error while loading shader files\n";
		std::cerr << e.what() << '\n';
	}

	Shader shader;
	shader.compile(vertexCode.c_str(), fragmentCode.c_str());
	return shader;
}

dat::Texture2D dat::ResourceManager::loadTextureFromFile(const char* textureFile, bool alpha)
{
	Texture2D texture;

	if (alpha)
	{
		texture.internalFormat = GL_RGBA;
		texture.imageFormat = GL_RGBA;
	}

	int width, height, numberChannels;
	unsigned char* data = stbi_load(textureFile, &width, &height, &numberChannels, 0);

	texture.generate(width, height, data);
	stbi_image_free(data);

	return texture;
}
