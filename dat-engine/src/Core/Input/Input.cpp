#include "Input.h"

namespace dat
{
	void Input::initialize(Window* window)
	{
		s_Window = window;
	}

	int Input::isKeyDown(const Key key)
	{
		return glfwGetKey(s_Window->window(), (int)key);
	}

	int Input::isMouseButtonDown(const MouseButton mouseButton)
	{
		return glfwGetMouseButton(s_Window->window(), (int)mouseButton);
	}

	glm::vec2 Input::getMousePosition()
	{
		double x, y;
		glfwGetCursorPos(s_Window->window(), &x, &y);

		return { float(x), float(y) };
	}
}