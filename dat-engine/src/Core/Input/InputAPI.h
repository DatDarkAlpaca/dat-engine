#pragma once
#include "Key.h"
#include "Window/Window.h"

namespace dat
{
	class InputAPI
	{
	public:
		InputAPI(Window& window);

	public:
		int isKeyDown(const Key key) const;

		int isMouseButtonDown(const Key key) const;

		glm::vec2 getMousePosition() const;
	
	public:
		Window& m_Window;
	};
}