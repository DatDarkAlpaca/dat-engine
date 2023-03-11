#pragma once
#include "glm/glm.hpp"

namespace dat 
{
	class DAT_API Shader
	{
	public:
		Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
		Shader() = default;
		~Shader();

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