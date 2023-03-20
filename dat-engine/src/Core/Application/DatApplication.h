#pragma once
#include "API.h"
#include "Window/Window.h"
#include "Layer/LayerStack.h"
#include "Core/Input/InputAPI.h"

namespace dat
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

	public:
		LayerStack& layers() { return m_LayerStack; }

	private:
		InputAPI* m_Input = nullptr;
		LayerStack m_LayerStack;
		Window m_Window;
	};
}
