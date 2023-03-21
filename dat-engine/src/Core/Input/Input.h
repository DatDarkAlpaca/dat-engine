#pragma once
#include "Key.h"
#include "Window/Window.h"

namespace dat
{
	class DAT_API Input
	{
	public:
		static void initialize(Window* window);

	public:
		static int isKeyDown(const Key key);

		static int isMouseButtonDown(const MouseButton mouseButton);

		static glm::vec2 getMousePosition();

	private:
		static inline Window* s_Window = nullptr;
	};
}