#pragma once
#include "pch.h"

namespace dat
{
	class DAT_API VertexBuffer
	{
	public:
		VertexBuffer(const std::vector<float>& data, GLenum usage = GL_STATIC_DRAW);

		VertexBuffer() = default;

		~VertexBuffer();

	public:
		void initialize(const std::vector<float>& data, GLenum usage);

	public:
		void bind() const;

		void unbind() const;

	private:
		unsigned int m_ID = -1;
	};
}