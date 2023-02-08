#include "pch.h"
#include "Window.h"
#include "Utils/Logger.h"
#include "InputHandler.h"
#include "ApplicationStatus.h"

// Callbacks:
static void GLFWErrorCallback(int errorCode, const char* description)
{
	DAT_CORE_ERROR("GLFW Error [{}]: {}", errorCode, description);
}

static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Window:
namespace dat::core 
{
	Window::Window(int width, int height, const char* title)
	{
		initializeGLFW();

		createWindow(width, height, title);

		setContext();

		initializeGLEW();
	}

	void Window::initializeGLFW()
	{
		if (applicationStatus.isGLFWInitialized)
			return;

		if (glfwInit() != GLFW_TRUE)
		{
			DAT_CORE_CRITICAL("Failed to initialize GLFW.");
			glfwTerminate();
		}

		glfwSetErrorCallback(GLFWErrorCallback);

		applicationStatus.isGLFWInitialized = true;
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

	void Window::initializeGLEW()
	{
		if (applicationStatus.isGLEWInitialized)
			return;

		if (glewInit() != GLEW_OK)
		{
			DAT_CORE_ERROR("Failed to initialize GLEW.");
			glfwTerminate();
		}

		applicationStatus.isGLEWInitialized = true;
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
