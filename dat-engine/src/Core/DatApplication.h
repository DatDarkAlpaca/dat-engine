#pragma once
#include "API.h"
#include "Window.h"

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

	private:
		Window m_Window;
	};
}
