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
	m_Window.setContext();

	initializeGLEW();

	//glEnable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shader.m_ID = shader.initializeProgram("res/vertex.glsl", "res/frag.glsl");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
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
		onRender();
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

void dat::core::DatApplication::onRender()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.3, 0.0, 0.5, 1.0);

	shader.bind();
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	m_Window.swapBuffers();
	m_Window.pollEvents();
}