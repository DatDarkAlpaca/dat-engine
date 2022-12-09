#include "pch.h"
#include "ImmediateRenderer2D.h"

namespace dat::graphics
{
	ImmediateRenderer2D::~ImmediateRenderer2D()
	{
		for (const IRenderCommand* command : m_RenderQueue)
			delete command;

		m_RenderQueue.clear();
	}

	void ImmediateRenderer2D::push(IRenderCommand* command)
	{
		m_RenderQueue.push_back(command);
	}

	void ImmediateRenderer2D::flush()
	{
		while (!m_RenderQueue.empty())
		{
			IRenderCommand* command = m_RenderQueue.front();
			command->execute();

			m_RenderQueue.pop_front();
		}
	}
}