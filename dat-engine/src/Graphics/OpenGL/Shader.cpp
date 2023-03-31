#include "pch.h"

#include "Shader.h"
#include "Utils/Logger.h"
#include "Utils/FileReader.h"

static std::vector<std::pair<std::string, int>> listActiveUniforms(unsigned int program)
{
	std::vector<std::pair<std::string, int>> uniforms;

	int count;
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);

	const int maxBufferSize = 24;
	for (size_t i = 0; i < count; i++)
	{
		int length, size;
		unsigned int type;
		char name[maxBufferSize];
		glGetActiveUniform(program, (GLuint)i, maxBufferSize, &length, &size, &type, name);
		
		uniforms.push_back({ name, i });
	}

	return uniforms;
}

namespace dat 
{
	Shader::Shader(unsigned int id)
		: m_ID(id)
	{
		for (const auto& [uniform, location] : listActiveUniforms(m_ID))
			m_Uniforms[uniform] = location;
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

	unsigned int Shader::getUniform(const std::string& uniformName) const
	{
		if (m_Uniforms.find(uniformName) == m_Uniforms.end())
		{
			DAT_CORE_WARN("The uniform {} does not exist.", uniformName.data());
			return -1;
		}

		return m_Uniforms.at(uniformName);
	}

	void Shader::setFloat(const char* name, float value)
	{
		glUniform1f(getUniform(name), value);
	}

	void Shader::setInteger(const char* name, int value)
	{
		glUniform1d(getUniform(name), value);
	}

	void Shader::setVector2f(const char* name, const glm::vec2& value)
	{
		glUniform2f(getUniform(name), value.x, value.y);
	}

	void Shader::setVector3f(const char* name, const glm::vec3& value)
	{
		glUniform3f(getUniform(name), value.x, value.y, value.z);
	}

	void Shader::setVector4f(const char* name, const glm::vec4& value)
	{
		glUniform4f(getUniform(name), value.x, value.y, value.z, value.w);
	}

	void Shader::setMatrix4f(const char* name, glm::mat4 matrix)
	{
		glUniformMatrix4fv(getUniform(name), 1, false, glm::value_ptr(matrix));
	}
}