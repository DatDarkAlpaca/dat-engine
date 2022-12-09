#pragma once
#include <memory>
#include <GL/glew.h>
#include "IRenderCommand.h"

namespace dat::graphics
{
	class IRenderer
	{
	public:
		virtual ~IRenderer() = default;

	public:
		virtual void begin() const { }

		virtual void push(IRenderCommand* command) = 0;

		virtual void flush() = 0;

		virtual void end() const { }

	public:
		virtual void clearColor(float red = 0.f, float green = 0.f, float blue = 0.f, float alpha = 1.f)
		{
			glClearColor(red, green, blue, alpha);
		}

		virtual void clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
	};
}