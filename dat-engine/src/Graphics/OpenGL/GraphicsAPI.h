#pragma once
#include "Application/ApplicationStatus.h"
#include "Utils/Logger.h"

namespace
{
	inline void GLFWErrorCallback(int errorCode, const char* description)
	{
		DAT_CORE_ERROR("GLFW Error [{}]: {}", errorCode, description);
	}
}

namespace dat
{
	inline void initializeGLFW()
	{
		if (applicationStatus.isGLFWInitialized)
		{
			DAT_CORE_WARN("GLFW is already initialized.");
			return;
		}

		if (glfwInit() != GLFW_TRUE)
		{
			DAT_CORE_CRITICAL("Failed to initialize GLFW.");
			glfwTerminate();
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		glfwSetErrorCallback(GLFWErrorCallback);

		applicationStatus.isGLFWInitialized = true;
	}

	inline void initializeGLEW()
	{
		if (applicationStatus.isGLEWInitialized)
		{
			DAT_CORE_WARN("GLEW is already initialized.");
			return;
		}

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			DAT_CORE_ERROR("Failed to initialize GLEW.");
			glfwTerminate();
			return;
		}

		applicationStatus.isGLEWInitialized = true;
	}
}