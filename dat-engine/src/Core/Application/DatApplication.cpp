#include "pch.h"
#include "Input/Input.h"
#include "Utils/Logger.h"
#include "DatApplication.h"
#include "Graphics/GraphicAPI.h"
#include "Event/EventsHeader.h"

namespace dat
{
	DatApplication::DatApplication(int width, int height, const char* title)
		: m_Window(width, height, title)
	{
		initialize();
	}

	void DatApplication::initialize()
	{
		initializeLogger();

		initializeGLFW();

		m_TimestepHandler = getTimestepHandler();

		m_Window.initialize();
		m_Window.setEventCallback(std::bind(&DatApplication::onEvent, this, std::placeholders::_1));

		Input::initialize(&m_Window);

		initializeGLEW();
	}

	void DatApplication::shutdown()
	{
		m_Window.close();

		glfwTerminate();
	}

	void DatApplication::run()
	{
		static double t = 0;

		while (!m_Window.isClosed())
		{
			Timestep dt = m_TimestepHandler->restart();
			
			m_LayerStack.onUpdate(dt);
			
			onRender();
		}

		shutdown();
	}

	void DatApplication::onEvent(IEvent& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.dispatch<WindowCloseEvent>([](WindowCloseEvent& closeEvent) -> bool {
			return true;
		});

		dispatcher.dispatch<WindowResizeEvent>([](WindowResizeEvent& resizeEvent) -> bool {
			glViewport(0, 0, resizeEvent.width, resizeEvent.height);
			return true;
		});

		m_LayerStack.onEvent(event);
	}

	void DatApplication::onRender()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0);

		m_LayerStack.onRender();

		m_Window.swapBuffers();
		m_Window.pollEvents();
	}
}