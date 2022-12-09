#pragma once
#include "Buffer.h"

namespace dat::graphics 
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

	public:
		void addBuffer(Buffer* buffer, GLuint location);

	public:
		inline void bind()   const { glBindVertexArray(m_ID); }

		inline void unbind() const { glBindVertexArray(0); }

	private:
		std::vector<Buffer*> m_Buffers;
		GLuint m_ID;
	};
}