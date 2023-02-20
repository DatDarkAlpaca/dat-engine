#include "pch.h"

#include "Window.h"
#include "Utils/Logger.h"
#include "InputHandler.h"
#include "ApplicationStatus.h"

// Callback:
static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Window:
namespace dat::core 
{
	Window::Window(int width, int height, const char* title)
		: m_Width(width), m_Height(height), m_Title(title)
	{
	}

	void Window::initialize()
	{
		createWindow(m_Width, m_Height, m_Title);

		setContext();
	
		setViewport(0, 0, m_Width, m_Height);
	}

	void Window::createWindow(int width, int height, const char* title)
	{
		m_Window = GLFWSmartWindow(glfwCreateWindow(width, height, title, nullptr, nullptr), GLFWWindowDeleter());

		if (!m_Window.get())
		{
			DAT_CORE_ERROR("Failed to initialize a GLFW window.");
			glfwTerminate();
		}

		glfwSetKeyCallback(window(), InputHandler::inputKeyCallback);

		glfwSetCursorPosCallback(window(), InputHandler::mousePositionCallback);

		glfwSetMouseButtonCallback(window(), InputHandler::mouseButtonCallback);

		glfwSetFramebufferSizeCallback(m_Window.get(), framebufferSizeCallback);
	}

	void Window::pollEvents() const
	{
		glfwPollEvents();
	}

	void Window::swapBuffers() const
	{
		glfwSwapBuffers(window());
	}

	void Window::setContext() const
	{
		glfwMakeContextCurrent(window());
	}

	void Window::setViewport(GLint x, GLint y, GLsizei width, GLsizei height) const
	{
		glViewport(x, y, width, height);
	}

	void Window::close()
	{
		m_Window.reset();
	}
}
