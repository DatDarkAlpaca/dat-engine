#include "VertexArray.h"
#include "pch.h"

namespace dat
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_ID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_ID);
	}

	void VertexArray::enableAttributes(const VertexAttributes& attributes)
	{
		unsigned offset = 0;
		for (const auto& attribute : attributes)
		{
			glVertexAttribPointer(attribute.location, attribute.size, attribute.type,
				attribute.normalized, attributes.stride(), (void*)offset);

			glEnableVertexAttribArray(attribute.location);

			offset += attribute.size * getAttributeSize(attribute.type);
		}
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_ID);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}
}
