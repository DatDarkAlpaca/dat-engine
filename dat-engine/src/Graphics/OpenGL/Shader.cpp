#include "pch.h"

#include "Shader.h"
#include "Utils/Logger.h"
#include "Utils/FileReader.h"
#include "Factories/ShaderFactory.h"

namespace dat 
{
	Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
	{
		m_ID = createShader(vertexShaderPath, fragmentShaderPath);
	}

	Shader::~Shader()
	{
		deleteProgram();
	}

	Shader& Shader::bind()
	{
		glUseProgram(m_ID);
		return *this;
	}

	void Shader::unbind() const
	{
		glUseProgram(0);
	}

	void Shader::deleteProgram() const
	{
		glDeleteProgram(m_ID);
	}

	void Shader::setFloat(const char* name, float value)
	{
		glUniform1f(glGetUniformLocation(m_ID, name), value);
	}

	void Shader::setInteger(const char* name, int value)
	{
		glUniform1d(glGetUniformLocation(m_ID, name), value);
	}

	void Shader::setVector2f(const char* name, const glm::vec2& value)
	{
		glUniform2f(glGetUniformLocation(m_ID, name), value.x, value.y);
	}

	void Shader::setVector3f(const char* name, const glm::vec3& value)
	{
		glUniform3f(glGetUniformLocation(m_ID, name), value.x, value.y, value.z);
	}

	void Shader::setVector4f(const char* name, const glm::vec4& value)
	{
		glUniform4f(glGetUniformLocation(m_ID, name), value.x, value.y, value.z, value.w);
	}

	void Shader::setMatrix4f(const char* name, glm::mat4 matrix)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, false, glm::value_ptr(matrix));
	}
}