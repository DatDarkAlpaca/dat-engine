#include "pch.h"
#include "DatApplication.h"
#include "Graphics/GraphicAPI.h"
#include "Event/EventsHeader.h"

#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/VertexAttributes.h"

static VertexArray* vao;
static VertexBuffer* vbo;

namespace dat
{
	DatApplication::DatApplication(int width, int height, const char* title)
		: m_Window(width, height, title)
	{
		initialize();
	}

	void DatApplication::initialize()
	{
		initializeGLFW();

		m_Window.initialize();
		m_Window.setEventCallback(std::bind(&DatApplication::onEvent, this, std::placeholders::_1));
		m_Window.setContext();

		initializeGLEW();

		shader = new Shader("res/vertex.glsl", "res/frag.glsl");

		// Graphics:
		vao = new VertexArray();
		vao->bind();

		std::vector<float> vertices = {
			-0.5f, -0.5f, 0.0f, 0.5f, 0.59f, 0.7f,
			 0.5f, -0.5f, 0.0f, 0.0, 0.0, 0.0,
			 0.0f,  0.5f, 0.0f, 0.1f, 0.54f, 0.3f,
		};
		vbo = new VertexBuffer(std::vector<float>(vertices), GL_STATIC_DRAW); 

		// Attributes:
		VertexAttributes attributes;
		attributes.addAttribute(0, 3, AttributeType::FLOAT, false);
		attributes.addAttribute(1, 3, AttributeType::FLOAT, false);

		vao->enableAttributes(attributes);

		vbo->unbind();
		vao->unbind();
	}

	void DatApplication::shutdown()
	{
		m_Window.close();

		glfwTerminate();
	}

	void DatApplication::run()
	{
		while (!m_Window.isClosed())
		{
			onRender();
		}

		shutdown();
	}

	void DatApplication::onEvent(IEvent& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.dispatch<WindowCloseEvent>([](WindowCloseEvent& closeEvent) -> bool {
			DAT_CORE_INFO("Window closing. Night night!");
			return true;
			});
	}

	void DatApplication::onRender()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.3, 0.0, 0.5, 1.0);

		shader->bind();
		vao->bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		m_Window.swapBuffers();
		m_Window.pollEvents();
	}
}