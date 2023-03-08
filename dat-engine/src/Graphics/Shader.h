#pragma once
#include "glm/glm.hpp"

// Todo: separate the file loading from the shader.
namespace dat 
{
	class Shader
	{
	public:
		Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
		~Shader();
		Shader() = default;

	public:
		unsigned int initializeProgram(const char* vertexShaderPath, const char* fragmentShaderPath);

	public:
		Shader& bind();

		void unbind() const;

		void deleteProgram() const;

	public:
		void setFloat(const char* name, float value);

		void setInteger(const char* name, int value);

		void setVector2f(const char* name, const glm::vec2& value);

		void setVector3f(const char* name, const glm::vec3& value);

		void setVector4f(const char* name, const glm::vec4& value);

		void setMatrix4f(const char* name, glm::mat4 matrix);

	public:
		unsigned int m_ID = 0;
	};
}