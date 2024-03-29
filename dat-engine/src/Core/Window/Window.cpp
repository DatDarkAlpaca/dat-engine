#include "pch.h"

#include "Window.h"
#include "Utils/Logger.h"
#include "Application/ApplicationStatus.h"

namespace dat 
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
			WindowInfo& info = *(WindowInfo*)glfwGetWindowUserPointer(window);
			WindowResizeEvent resizeEvent(width, height);
			info.eventCallback(resizeEvent);
		});

		glfwSetCursorPosCallback(m_Window.get(), [](GLFWwindow* window, double x, double y) {
			WindowInfo& info = *(WindowInfo*)glfwGetWindowUserPointer(window);
			MouseMoveEvent mouseMove(x, y);
			info.eventCallback(mouseMove);
		});

		glfwSetMouseButtonCallback(m_Window.get(), [](GLFWwindow* window, int button, int action, int mods) {
			WindowInfo& info = *(WindowInfo*)glfwGetWindowUserPointer(window);
			
			switch (action)
			{
				case InputAction::INPUT_RELEASE:
				{
					MouseReleasedEvent releasedEvent((MouseButton)button, (Mods)mods);
					info.eventCallback(releasedEvent);
					return;
				}

				case InputAction::INPUT_PRESS:
				{
					MousePressedEvent pressEvent((MouseButton)button, (Mods)mods);
					info.eventCallback(pressEvent);
					return;
				}

				case InputAction::INPUT_REPEAT:
				{
					MouseRepeatEvent repeatEvent((MouseButton)button, (Mods)mods);
					info.eventCallback(repeatEvent);
					return;
				}
			}
		});
	
		glfwSetScrollCallback(m_Window.get(), [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowInfo& info = *(WindowInfo*)glfwGetWindowUserPointer(window);
			MouseScrollEvent scrollEvent(xOffset, yOffset);
			info.eventCallback(scrollEvent);
		});

		glfwSetKeyCallback(m_Window.get(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowInfo& info = *(WindowInfo*)glfwGetWindowUserPointer(window);
			
			switch (action)
			{
				case InputAction::INPUT_RELEASE:
				{
					KeyReleasedEvent releasedEvent((Key)key, (Mods)mods);
					info.eventCallback(releasedEvent);
					return;
				}

				case InputAction::INPUT_PRESS:
				{
					KeyPressedEvent pressEvent((Key)key, (Mods)mods);
					info.eventCallback(pressEvent);
					return;
				}

				case InputAction::INPUT_REPEAT:
				{
					KeyRepeatEvent repeatEvent((Key)key, (Mods)mods);
					info.eventCallback(repeatEvent);
					return;
				}
			}
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
