#include "pch.h"
#include "Window.h"

void dat::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

dat::Window::Window(int width, int height, const char* title)
{
	m_Window = GLFWSmartWindow(glfwCreateWindow(width, height, title, nullptr, nullptr), GLFWWindowDeleter());
	
	if (!m_Window.get())
	{
		std::cerr << "[Error]: Failed to create a GLFW window.\n";
		glfwTerminate();
	}

	glfwSetFramebufferSizeCallback(m_Window.get(), framebufferSizeCallback);
}

void dat::Window::setContext() const
{
	glfwMakeContextCurrent(m_Window.get());
}

void dat::Window::setViewport(GLint x, GLint y, GLsizei width, GLsizei height) const
{
	glViewport(x, y, width, height);
}

void dat::Window::close()
{
	m_Window.reset();
}
