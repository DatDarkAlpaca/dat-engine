#include "pch.h"
#include "Camera.h"

namespace dat::core
{
	Camera::Camera(int width, int height, glm::vec3 position)
		: m_Width(width), m_Height(height), m_Position(position)
	{

	}

	void Camera::updatePerspective(float fov, float nearPlane, float farPlane, dat::graphics::Shader shader, const std::string& projUniformName)
	{
		glm::mat4 projection(1.f);
		projection = glm::perspective(glm::radians(fov), float(m_Width / m_Height), nearPlane, farPlane);

		shader.bind().setMatrix4f(projUniformName.c_str(), projection);
	}

	void Camera::updateView(Shader& shader, const std::string& viewUniformName)
	{
		glm::mat4 view(1.f);
		view = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);

		shader.bind().setMatrix4f(viewUniformName.c_str(), view);
	}

	void Camera::handleEvents(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			m_Position += 100.f * m_Orientation;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			m_Position -= 100.f * m_Orientation;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			m_Position += m_Orientation;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			m_Position += m_Orientation;
		}
	}
}