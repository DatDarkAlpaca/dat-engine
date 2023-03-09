#include "VertexBuffer.h"

namespace dat
{
	VertexBuffer::VertexBuffer(const std::vector<float>& data, GLenum usage)
	{
		initialize(data, usage);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	void VertexBuffer::initialize(const std::vector<float>& data, GLenum usage)
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), usage);
	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}

	void VertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

