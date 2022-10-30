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
		static std::shared_ptr<Shader> loadShader(std::string_view shaderName, const char* vertexShaderFile, const char* fragmentShaderFile);

		static std::shared_ptr<Shader> getShader(std::string_view shaderName);

		static std::shared_ptr<Texture2D> loadTexture(std::string_view textureName, const char* textureFile, bool alpha);

		static std::shared_ptr<Texture2D> getTexture(std::string_view textureName);

	private:
		static Shader loadShaderFromFile(const char* vertexShaderFile, const char* fragmentShaderFile);

		static Texture2D loadTextureFromFile(const char* textureFile, bool alpha);

	private:
		static inline std::unordered_map<std::string_view, std::shared_ptr<Shader>> m_Shaders = {};
		static inline std::unordered_map<std::string_view, std::shared_ptr<Texture2D>> m_Textures = {};
	};
}