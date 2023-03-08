#pragma once
#include "pch.h"
#include "Event/EventsHeader.h"

namespace dat
{
	struct GLFWWindowDeleter
	{
		void operator()(GLFWwindow* windowPtr)
		{
			glfwDestroyWindow(windowPtr);
		}
	};

	class DAT_API Window
	{
		using GLFWSmartWindow = std::unique_ptr<GLFWwindow, GLFWWindowDeleter>;

	public:
		Window(int width, int height, const char* title);

	public:
		void initialize();

	private:
		void createWindow();

	public:
		void pollEvents() const;

		void swapBuffers() const;

	public:
		void setContext() const;

		void setViewport(GLint x, GLint y, GLsizei width, GLsizei height) const;

		void setEventCallback(const std::function<void(IEvent&)>& callback);

	public:
		inline bool isClosed() const { return glfwWindowShouldClose(window()); }

		void close();

	public:
		GLFWwindow* window() const { return m_Window.get(); }

	private:
		GLFWSmartWindow m_Window = nullptr;

	private:
		struct WindowInfo
		{
		public:
			WindowInfo(int width, int height, const char* title)
				: width(width), height(height), title(title) { }

		public:
			std::function<void(IEvent&)> eventCallback = {};

		public:
			const char* title = nullptr;
			int width = 0, height= 0;
		} m_Info;
	};
}