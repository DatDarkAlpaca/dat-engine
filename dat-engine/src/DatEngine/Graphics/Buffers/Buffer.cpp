#include "pch.h"
#include "Buffer.h"

namespace dat::graphics 
{
	Buffer::Buffer(float* data, size_t count, unsigned int componentCount)
		: m_ComponentCount(componentCount)
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);

		glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(1, &m_ID);
	}
}
