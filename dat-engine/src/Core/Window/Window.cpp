#include "pch.h"

#include "Window.h"
#include "Utils/Logger.h"
#include "Application/ApplicationStatus.h"

namespace dat::core 
{
	Window::Window(int width, int height, const char* title)
		: m_Info(width, height, title)
	{
	}

	void Window::initialize()
	{
		createWindow();

		setContext();
	
		setViewport(0, 0, m_Info.width, m_Info.height);
	}

	void Window::createWindow()
	{
		m_Window = GLFWSmartWindow(glfwCreateWindow(
			m_Info.width, m_Info.height, 
			m_Info.title, nullptr, nullptr), 
		GLFWWindowDeleter());

		if (!m_Window.get())
		{
			DAT_CORE_ERROR("Failed to initialize a GLFW window.");
			glfwTerminate();
			return;
		}

		glfwSetWindowUserPointer(window(), &m_Info);

		glfwSetWindowCloseCallback(window(), [](GLFWwindow* window)
		{
			WindowInfo& info = *(WindowInfo*)glfwGetWindowUserPointer(window);
			WindowCloseEvent closeEvent;
			info.eventCallback(closeEvent);
		});

		glfwSetFramebufferSizeCallback(m_Window.get(), [](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		});
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

	void Window::setEventCallback(const std::function<void(IEvent&)>& callback)
	{
		m_Info.eventCallback = callback;
	}

	void Window::close()
	{
		m_Window.reset();
	}
}