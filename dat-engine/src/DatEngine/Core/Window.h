#pragma once
#include "pch.h"

namespace dat::core 
{
	struct GLFWWindowDeleter
	{
		void operator()(GLFWwindow* windowPtr)
		{
			glfwDestroyWindow(windowPtr);
		}
	};

	class Window
	{
		using GLFWSmartWindow = std::unique_ptr<GLFWwindow, GLFWWindowDeleter>;

	public:
		Window(int width, int height, const char* title);

	private:
		void initializeGLFW();

		void initializeGLEW();

		void createWindow(int width, int height, const char* title);

	public:
		void update() const;

	public:
		void setContext() const;

		void setViewport(GLint x, GLint y, GLsizei width, GLsizei height) const;

	public:
		inline bool isClosed() const { return glfwWindowShouldClose(window()); }

		void close();

	public:
		GLFWwindow* window() const { return m_Window.get(); }

	private:
		GLFWSmartWindow m_Window = nullptr;
	};
}