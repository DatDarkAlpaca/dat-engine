#pragma once
#include "API.h"
#include "Window.h"

namespace dat::core
{
	void initializeGLFW();

	class DAT_API DatApplication
	{
	public:
		DatApplication(int width, int height, const char* title);

	private:
		void initialize();

	public:
		void run();

	private:
		Window m_Window;
	};
}
