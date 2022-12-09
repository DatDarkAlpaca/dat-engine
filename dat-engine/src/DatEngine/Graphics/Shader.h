#pragma once

namespace dat::graphics 
{
	class Shader
	{
	public:
		Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
		Shader() = default;
		~Shader();

	private:
		unsigned int initializeProgram();

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

	private:
		unsigned int m_ID = 0;

		const char* m_VertexShaderPath, *m_FragmentShaderPath;
	};
}