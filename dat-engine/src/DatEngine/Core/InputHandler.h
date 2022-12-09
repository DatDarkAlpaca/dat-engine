#pragma once
#include "pch.h"

namespace dat::core 
{
	class InputHandler
	{
	public:
		static void inputKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
		{
			if (key >= 0 && key < 1024)
			{
				if (action == GLFW_PRESS)
					m_Keys[key] = true;
				else if (action == GLFW_RELEASE)
					m_Keys[key] = false;
			}
		}

		static void mousePositionCallback(GLFWwindow* window, double xpos, double ypos)
		{
			m_Xpos = xpos;
			m_YPos = ypos;
		}

		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
		{
			if (button >= 0 && button < 8)
			{
				m_MousePressed[button] = action;
			}
		}

		static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
		{
			m_Scroll = -yoffset;
		}

	public:
		static bool isKeyPressed(GLuint key)
		{
			if (key < 0 || key >= 1024)
				return false;

			return m_Keys[key];
		}

		static bool isMousePressed(int button)
		{
			if (button < 0 || button >= 8)
				return false;

			return m_MousePressed[button] == GLFW_PRESS;
		}

		static bool isMouseReleased(int button)
		{
			if (button < 0 || button >= 8)
				return false;

			return m_MousePressed[button] == GLFW_RELEASE;
		}

		static bool isMouseRepeat(int button)
		{
			if (button < 0 || button >= 8)
				return false;

			return m_MousePressed[button] == GLFW_REPEAT;
		}

		static double scrollOffset()
		{
			return m_Scroll;
		}
		
		static glm::vec2 mousePosition()
		{
			return { m_Xpos, m_YPos };
		}

	private:
		static inline bool m_Keys[1024] = {};
		static inline double m_Scroll = 0.0;

	private:
		static inline double m_Xpos, m_YPos;
		static inline short m_MousePressed[8];
	};
}