#pragma once
#include <GL/glew.h>

namespace dat::graphics 
{
	class Buffer
	{
	public:
		Buffer(float* data, size_t count, unsigned int componentCount);
		~Buffer();

	public:
		inline void bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_ID); }

		inline void unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

	public:
		inline unsigned int getComponentCount() const { return m_ComponentCount; }

	private:
		unsigned int m_ID;
		unsigned int m_ComponentCount;
	};
}