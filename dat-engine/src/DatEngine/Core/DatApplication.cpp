#include "pch.h"
#include "DatApplication.h"

dat::core::DatApplication::DatApplication(int width, int height, const char* title)
	: m_Window(width, height, title)
{

}

void dat::core::DatApplication::initialize()
{

}

void dat::core::DatApplication::run()
{
	while (!m_Window.isClosed())
	{
		m_Window.pollEvents();

		m_Window.swapBuffers();
	}
}
