#pragma once
#include "Graphics/GraphicsSpecification.hpp"
#include "Platform/GLFW/Window/Window_GLFW.hpp"

namespace dat::platform::gl
{
	void SetupOpenGLWindowing(Window& window, const WindowProperties&, const graphics::GraphicsSpecification&);
}