#include "pch.h"
#include "Shader.h"

namespace
{
	inline void checkCompileErrors(unsigned int object)
	{
		int success;
		char infoLog[1024];

		glGetShaderiv(object, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(object, 512, NULL, infoLog);
			DAT_CORE_ERROR("Shader Error:\n{}", infoLog);
		}
	}

	inline void checkLinkErrors(unsigned int object)
	{
		int success;
		char infoLog[1024];

		glGetProgramiv(object, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetProgramInfoLog(object, 1024, nullptr, infoLog);
			DAT_CORE_ERROR("Linking Error:\n{}", infoLog);
		}
	}


void dat::Shader::compile(const char* vertexSource, const char* fragmentSource)
{
	unsigned int vertexShader, fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);
	checkCompileErrors(fragmentShader);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);
	checkLinkErrors(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void dat::Shader::setFloat(const char* name, float value)
{
	glUniform1f(glGetUniformLocation(ID, name), value);
}

void dat::Shader::setInteger(const char* name, int value)
{
	glUniform1d(glGetUniformLocation(ID, name), value);
}

void dat::Shader::setVector2f(const char* name, const glm::vec2& value)
{
	glUniform2f(glGetUniformLocation(ID, name), value.x, value.y);
}

void dat::Shader::setVector3f(const char* name, const glm::vec3& value)
{
	glUniform3f(glGetUniformLocation(ID, name), value.x, value.y, value.z);
}

void dat::Shader::setVector4f(const char* name, const glm::vec4& value)
{
	glUniform4f(glGetUniformLocation(ID, name), value.x, value.y, value.z, value.w);
}

void dat::Shader::setMatrix4f(const char* name, glm::mat4 matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, false, glm::value_ptr(matrix));
}

dat::Shader& dat::Shader::use()
{
	glUseProgram(ID);
	return *this;
}
