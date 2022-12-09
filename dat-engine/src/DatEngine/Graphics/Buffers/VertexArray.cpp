#include "pch.h"
#include "VertexArray.h"

namespace dat::graphics
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_ID);
	}

	VertexArray::~VertexArray()
	{
		for (size_t i = 0; i < m_Buffers.size(); ++i)
			delete m_Buffers[i];

		glDeleteVertexArrays(1, &m_ID);
	}

	void VertexArray::addBuffer(Buffer* buffer, GLuint location)
	{
		bind();
		buffer->bind();

		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

		buffer->unbind();
		unbind();
	}
}