#include "pch.h"
#include "DatApplication.h"
#include "Graphics/GraphicAPI.h"
#include "Event/EventsHeader.h"

dat::core::DatApplication::DatApplication(int width, int height, const char* title)
	: m_Window(width, height, title)
{
	initialize();
}

void dat::core::DatApplication::initialize()
{
	initializeGLFW();

	m_Window.initialize();
	m_Window.setEventCallback(std::bind(&DatApplication::onEvent, this, std::placeholders::_1));

	initializeGLEW();

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void dat::core::DatApplication::shutdown()
{
	m_Window.close();

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

void dat::core::DatApplication::onEvent(IEvent& event)
{
	EventDispatcher dispatcher(event);

	dispatcher.dispatch<WindowCloseEvent>([](WindowCloseEvent& closeEvent) -> bool {
		DAT_CORE_INFO("Window closing. Night night!");
		return true;
	});
}