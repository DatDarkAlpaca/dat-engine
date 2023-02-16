#pragma once
#include "pch.h"
#include "Core/ApplicationStatus.h"

namespace
{
	inline void GLFWErrorCallback(int errorCode, const char* description)
	{
		DAT_CORE_ERROR("GLFW Error [{}]: {}", errorCode, description);
	}
}

namespace dat::core
{
	inline void initializeGLFW()
	{
		if (applicationStatus.isGLFWInitialized)
			return;

		if (glfwInit() != GLFW_TRUE)
		{
			DAT_CORE_CRITICAL("Failed to initialize GLFW.");
			glfwTerminate();
		}

		glfwSetErrorCallback(GLFWErrorCallback);

		applicationStatus.isGLFWInitialized = true;
	}

	inline void initializeGLEW()
	{
		if (applicationStatus.isGLEWInitialized)
			return;

		if (glewInit() != GLEW_OK)
		{
			DAT_CORE_ERROR("Failed to initialize GLEW.");
			glfwTerminate();
		}

		applicationStatus.isGLEWInitialized = true;
	}
}