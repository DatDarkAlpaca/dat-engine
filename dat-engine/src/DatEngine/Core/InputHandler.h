#pragma once
#include "pch.h"

namespace dat
{
	class InputHandler
	{
	public:
		static void inputKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
		{
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
				glfwSetWindowShouldClose(window, true);

			if (key >= 0 && key < 1024)
			{
				if (action == GLFW_PRESS)
					m_Keys[key] = true;
				else if (action == GLFW_RELEASE)
					m_Keys[key] = false;
			}
		}

	public:
		static bool isKeyPressed(GLuint key)
		{
			return m_Keys[key];
		}

	public:
		static inline bool m_Keys[1024] = {};
	};
}