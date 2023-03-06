#pragma once
#include "API.h"
#include "Window/Window.h"
#include "Core/TinyRenderer.h"

namespace dat::core
{
	class DAT_API DatApplication
	{
	public:
		DatApplication(int width, int height, const char* title);

	private:
		void initialize();

		void shutdown();

	public:
		void run();

	private:
		void onEvent(IEvent& event);

		void onRender();

	private:
		Window m_Window;
		TinyRenderer m_Renderer;
		unsigned int vao = 0, vbo = 0;

		Shader shader;
	};
}
