#pragma once
#include "pch.h"
#include "DatEngine/Graphics/Shader.h"
#include "DatEngine/Graphics/Texture.h"

namespace dat
{
	class ResourceManager
	{
	public:
		static void clear();

	public:
		static Shader loadShader(std::string_view shaderName, const char* vertexShaderFile, const char* fragmentShaderFile);

		static Shader getShader(std::string_view shaderName);

		static Texture2D loadTexture(std::string_view textureName, const char* textureFile, bool alpha);

		static Texture2D getTexture(std::string_view textureName);

	private:
		static Shader loadShaderFromFile(const char* vertexShaderFile, const char* fragmentShaderFile);

		static Texture2D loadTextureFromFile(const char* textureFile, bool alpha);

	private:
		static inline std::unordered_map<std::string_view, Shader> m_Shaders = {};
		static inline std::unordered_map<std::string_view, Texture2D> m_Textures = {};
	};
}