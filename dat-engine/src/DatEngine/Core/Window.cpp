#include "pch.h"
#include "Window.h"

static void GLFWErrorCallback(int errorCode, const char* description)
{
	DAT_CORE_ERROR("GLFW Error [{}]: {}", errorCode, description);
}

void dat::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

dat::Window::Window(int width, int height, const char* title)
{
	initializeGLFW();

	m_Window = GLFWSmartWindow(glfwCreateWindow(width, height, title, nullptr, nullptr), GLFWWindowDeleter());
	
	if (!m_Window.get())
	{
		DAT_CORE_ERROR("Failed to initialize a GLFW window.");
		glfwTerminate();
	}

	glfwSetFramebufferSizeCallback(m_Window.get(), framebufferSizeCallback);
}

void dat::Window::initializeGLFW()
{
	if (glfwInit() != GLFW_TRUE)
	{
		DAT_CORE_CRITICAL("Failed to initialize GLFW.");
		glfwTerminate();
	}

	glfwSetErrorCallback(GLFWErrorCallback);
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
