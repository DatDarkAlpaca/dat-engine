#pragma once

namespace dat
{
	class Shader
	{
	public:
		void compile(const char* vertexSource, const char* fragmentSource);

	public:
		void setFloat(const char* name, float value);

		void setInteger(const char* name, int value);

		void setVector2f(const char* name, const glm::vec2& value);

		void setVector3f(const char* name, const glm::vec3& value);

		void setVector4f(const char* name, const glm::vec4& value);

		void setMatrix4f(const char* name, glm::mat4 matrix);

	public:
		Shader& use();

	public:
		unsigned int ID = 0;
	};
}
