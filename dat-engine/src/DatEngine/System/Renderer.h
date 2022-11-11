#pragma once
#include "DatEngine/Core/Window.h"

namespace dat
{
	class Renderer
	{
	public:
		void initialize(std::unique_ptr<Window>& window, int width, int height)
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			DAT_CORE_TRACE("Sucessfully initialized GLFW");

			if (glewInit() != GLEW_OK)
				DAT_CORE_CRITICAL("Failed to initialize GLEW.");
			else
				DAT_CORE_TRACE("Sucessfully initialized GLEW");

			window->setViewport(0, 0, width, height);
		}

		void shutdown()
		{
		}
	};
}