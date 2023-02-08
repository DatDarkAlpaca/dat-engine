#include "pch.h"
#include "InputHandler.h"

void dat::core::InputHandler::inputKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			m_Keys[key] = true;
		else if (action == GLFW_RELEASE)
			m_Keys[key] = false;
	}
}

void dat::core::InputHandler::mousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	m_Xpos = xpos;
	m_YPos = ypos;
}

void dat::core::InputHandler::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button >= 0 && button < 8)
	{
		m_MousePressed[button] = action;
	}
}

void dat::core::InputHandler::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	m_Scroll = -yoffset;
}

bool dat::core::InputHandler::isKeyPressed(GLuint key)
{
	if (key < 0 || key >= 1024)
		return false;

	return m_Keys[key];
}

bool dat::core::InputHandler::isMousePressed(int button)
{
	if (button < 0 || button >= 8)
		return false;

	return m_MousePressed[button] == GLFW_PRESS;
}

bool dat::core::InputHandler::isMouseReleased(int button)
{
	if (button < 0 || button >= 8)
		return false;

	return m_MousePressed[button] == GLFW_RELEASE;
}

bool dat::core::InputHandler::isMouseRepeat(int button)
{
	if (button < 0 || button >= 8)
		return false;

	return m_MousePressed[button] == GLFW_REPEAT;
}

double dat::core::InputHandler::scrollOffset()
{
	return m_Scroll;
}

glm::vec2 dat::core::InputHandler::mousePosition()
{
	return { m_Xpos, m_YPos };
}
