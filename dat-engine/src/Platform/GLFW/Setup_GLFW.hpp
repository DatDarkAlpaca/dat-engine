#pragma once
#include "Core/Logger/Logger.hpp"

#include <GLFW/glfw3.h>

namespace
{
	inline void GLFWErrorCallback(int errorCode, const char* description)
	{
		DAT_LOG_ERROR("[GLFW]: {} [{}]", description, errorCode);
	}
}

namespace dat::platform
{
	inline void InitializePlatform()
	{
		glfwSetErrorCallback(GLFWErrorCallback);

		if (!glfwInit())
			DAT_LOG_CRITICAL("Failed to initialize the platform system.");
	}
}