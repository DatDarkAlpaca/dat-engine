#pragma once
#include "pch.h"

namespace dat::core 
{
	class InputHandler
	{
	public:
		static void inputKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

		static void mousePositionCallback(GLFWwindow* window, double xpos, double ypos);

		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

		static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	public:
		static bool isKeyPressed(GLuint key);

		static bool isMousePressed(int button);

		static bool isMouseReleased(int button);

		static bool isMouseRepeat(int button);

		static double scrollOffset();
		
		static glm::vec2 mousePosition();

	private:
		static inline bool m_Keys[1024] = {};
		static inline double m_Scroll = 0.0;

	private:
		static inline double m_Xpos, m_YPos;
		static inline short m_MousePressed[8];
	};
}