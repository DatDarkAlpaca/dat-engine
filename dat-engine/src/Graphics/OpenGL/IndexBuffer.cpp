#include "IndexBuffer.h"

namespace dat
{
	IndexBuffer::IndexBuffer(const std::vector<unsigned int>& data, GLenum usage)
	{
		initialize(data, usage);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	void IndexBuffer::initialize(const std::vector<unsigned int>& data, GLenum usage)
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), usage);
	}

	void IndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}

	void IndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}