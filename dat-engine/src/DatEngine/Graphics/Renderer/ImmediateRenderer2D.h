#pragma once
#include <deque>
#include "IRenderer.h"

namespace dat::graphics
{
	class ImmediateRenderer2D : public IRenderer
	{
	public:
		~ImmediateRenderer2D(); 

	public:
		void push(IRenderCommand* command) final;

		void flush() final;

	private:
		std::deque<IRenderCommand*> m_RenderQueue;
	};
}