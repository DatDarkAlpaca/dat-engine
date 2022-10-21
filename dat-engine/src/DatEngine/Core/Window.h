#pragma once
#include "pch.h"

namespace dat
{
	struct GLFWWindowDeleter
	{
		void operator()(GLFWwindow* windowPtr)
		{
			glfwDestroyWindow(windowPtr);
		}
	};

	void framebufferSizeCallback(GLFWwindow* window, int width, int height);

	class Window
	{
		using GLFWSmartWindow = std::unique_ptr<GLFWwindow, GLFWWindowDeleter>;

	public:
		Window(int width, int height, const char* title);

	public:
		void setContext() const;

		void setViewport(GLint x, GLint y, GLsizei width, GLsizei height) const;

		void close();

	public:
		GLFWwindow* window() const { return m_Window.get(); }

	private:
		GLFWSmartWindow m_Window = nullptr;
	};
}