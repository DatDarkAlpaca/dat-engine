#pragma once
#include "pch.h"

namespace dat::graphics 
{
	class IndexBuffer
	{
	public:
		IndexBuffer(GLushort* data, GLsizei count);

		~IndexBuffer();

	public:
		inline void bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID); }

		inline void unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

	public:
		inline unsigned int getIndexCount() const { return m_IndexCount; }

	private:
		unsigned int m_ID;
		unsigned int m_IndexCount;
	};
}