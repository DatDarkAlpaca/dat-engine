#include "InputAPI.h"

namespace dat
{
	InputAPI::InputAPI(Window& window)
		: m_Window(window) 
	{

	}

	int InputAPI::isKeyDown(const Key key) const
	{
		return glfwGetKey(m_Window.window(), (int)key);;
	}

	int InputAPI::isMouseButtonDown(const Key key) const
	{
		return glfwGetMouseButton(m_Window.window(), (int)key);
	}

	glm::vec2 InputAPI::getMousePosition() const
	{
		double x, y;
		glfwGetCursorPos(m_Window.window(), &x, &y);

		return { float(x), float(y) };
	}

}