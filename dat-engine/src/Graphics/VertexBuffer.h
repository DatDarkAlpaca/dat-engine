#pragma once
#include "pch.h"

namespace dat
{
	class VertexBuffer
	{
	public:
		VertexBuffer(const std::vector<float>& data, GLenum usage = GL_STATIC_DRAW);

		VertexBuffer() = default;

		~VertexBuffer();

	public:
		void initialize(const std::vector<float>& data, GLenum usage);

	public:
		void bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_ID); }

		void unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

	private:
		unsigned int m_ID = -1;
	};
}