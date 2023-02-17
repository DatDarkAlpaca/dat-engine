#include "pch.h"
#include "DatApplication.h"
#include "Graphics/GraphicAPI.h"

#include "Graphics/Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Shader:
	dat::graphics::Shader testShader("./src/vertex.glsl", "./src/frag.glsl");

	// Objects:
	float vertices[] = {
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,  // top right
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f   // top left 
	};

	int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Textures:
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("src/character.png", &width, &height, &nrChannels, 0);
	
	if(nrChannels == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	if (nrChannels == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	testShader.bind();
	testShader.setInteger("u_texture", 0);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	while (!m_Window.isClosed())
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
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
