#pragma once
#include "pch.h"
#include "Graphics/OpenGL/Shader.h"
#include "Utils/FileReader.h"

namespace
{
#ifdef DAT_DEBUG
	inline std::string shaderTypeStr(unsigned int shaderType)
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
			return "Unknown Shader";
		}
	}
#endif
	
	inline unsigned int compileShader(const char* filepath, unsigned int type)
	{
		unsigned int shader = glCreateShader(type);
		std::string vertexSource = dat::readFile(filepath);

		const char* vertexSrc = vertexSource.c_str();
		glShaderSource(shader, 1, &vertexSrc, NULL);
		glCompileShader(shader);

		return shader;
	}

	inline void checkCompileErrors(unsigned int shader, unsigned int type)
	{
		int success;
		char infoLog[1024];

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);

			DAT_CORE_ERROR("{} Shader Error:\n{}", shaderTypeStr(type), infoLog);

			glDeleteShader(shader);
		}
	}

	inline void checkLinkErrors(unsigned int program)
	{
		int success;
		char infoLog[1024];

		glGetProgramiv(program, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetProgramInfoLog(program, 1024, nullptr, infoLog);
			DAT_CORE_ERROR("Linking Error:\n{}", infoLog);

			glDeleteProgram(program);
		}
	}
}

namespace dat
{
	inline unsigned int createShader(const char* vertexShaderPath, const char* fragmentShaderPath)
	{
		unsigned int vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER);
		checkCompileErrors(vertexShader, GL_VERTEX_SHADER);

		unsigned int fragmentShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
		checkCompileErrors(fragmentShader, GL_FRAGMENT_SHADER);

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
