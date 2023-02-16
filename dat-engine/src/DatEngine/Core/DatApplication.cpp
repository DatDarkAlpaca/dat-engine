#include "pch.h"
#include "DatApplication.h"
#include "Graphics/GraphicAPI.h"

#include "Graphics/Shader.h"

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
}

void dat::core::DatApplication::shutdown()
{
	glfwTerminate();
}

void dat::core::DatApplication::run()
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // bottom left
		 0.5f, -0.5f, 0.0f, // bottom right
		 0.5f,  0.5f, 0.0f, // top right
		-0.5f,  0.5f, 0.0f, // top left
	};

	int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	dat::graphics::Shader testShader("./src/vertex.glsl", "./src/frag.glsl");

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	while (!m_Window.isClosed())
	{
		glClear(GL_COLOR_BUFFER_BIT);

		testShader.bind();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		m_Window.pollEvents();
		m_Window.swapBuffers();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &EBO);
	testShader.deleteProgram();

	shutdown();
}
