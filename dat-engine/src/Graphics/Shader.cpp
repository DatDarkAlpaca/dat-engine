#include "pch.h"

#include "Shader.h"
#include "Utils/Logger.h"
#include "Utils/FileReader.h"

namespace
{
	static std::string shaderTypeStr(unsigned int shaderType)
	{
		switch (shaderType)
		{
		case GL_VERTEX_SHADER:
			return "Vertex";
		case GL_FRAGMENT_SHADER:
			return "Fragment";
		case GL_GEOMETRY_SHADER:
			return "Geometry";
		default:
			return "";
		}
	}

	static void checkCompileErrors(unsigned int object, unsigned int type)
	{
		int success;
		char infoLog[1024];

		glGetShaderiv(object, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(object, 512, NULL, infoLog);

			DAT_CORE_ERROR("{} Shader Error:\n{}", shaderTypeStr(type), infoLog);

			glDeleteShader(object);
		}
	}

	static unsigned int compileShader(const char* filepath, unsigned int type)
	{
		unsigned int shader = glCreateShader(type);
		std::string vertexSource = dat::readFile(filepath);

		const char* vertexSrc = vertexSource.c_str();
		glShaderSource(shader, 1, &vertexSrc, NULL);
		glCompileShader(shader);

		checkCompileErrors(shader, type);

		return shader;
	}

	static void checkLinkErrors(unsigned int object)
	{
		int success;
		char infoLog[1024];

		glGetProgramiv(object, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetProgramInfoLog(object, 1024, nullptr, infoLog);
			DAT_CORE_ERROR("Linking Error:\n{}", infoLog);

			glDeleteProgram(object);
		}
	}

	static unsigned int createProgram(const char* vertexShaderPath, const char* fragmentShaderPath)
	{
		unsigned int vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER);

		unsigned int fragmentShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

		unsigned int program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);
		glValidateProgram(program);

		checkLinkErrors(program);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return program;
	}
}

namespace dat 
{
	Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
	{
		m_ID = createProgram(vertexShaderPath, fragmentShaderPath);
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