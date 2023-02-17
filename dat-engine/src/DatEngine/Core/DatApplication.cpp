#include "pch.h"
#include "DatApplication.h"
#include "Graphics/GraphicAPI.h"

#include "Graphics/Shader.h"
#include "Graphics/Texture2D.h"

#include "Core/Camera.h"

dat::core::DatApplication::DatApplication(int width, int height, const char* title)
	: m_Window(width, height, title)
{
	initialize();
}

void dat::core::DatApplication::initialize()
{
	initializeGLFW();

	m_Window.initialize();

	initializeGLEW();

	glEnable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void dat::core::DatApplication::shutdown()
{
	glfwTerminate();
}

void dat::core::DatApplication::run()
{
	while (!m_Window.isClosed())
	{
		glClear(GL_COLOR_BUFFER_BIT);

		m_Window.pollEvents();
		m_Window.swapBuffers();
	}

	shutdown();
}
