#pragma once
#include "pch.h"
#include "API.h"
#include "Graphics/Shader.h"

namespace dat::core
{
	using namespace dat::graphics;

	class Camera
	{
	public:
		Camera(int width, int height, glm::vec3 position);

	public:
		void updatePerspective(float fov, float nearPlane, float farPlane, dat::graphics::Shader shader, const std::string& projUniformName);

		void updateView(Shader& shader, const std::string& viewUniformName);

		void handleEvents(GLFWwindow* window);

	private:
		const glm::vec3 m_Orientation = glm::vec3(0.f, 0.f, -1.f), m_Up = glm::vec3(0.f, 1.f, 0.f);
		glm::vec3 m_Position;

		int m_Width, m_Height;
	};
}