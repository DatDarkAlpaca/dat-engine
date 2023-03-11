#pragma once
#include "pch.h"

namespace dat
{
	class DAT_API IndexBuffer
	{
	public:
		IndexBuffer(const std::vector<unsigned int>& data, GLenum usage = GL_STATIC_DRAW);

		IndexBuffer() = default;

		~IndexBuffer();

	public:
		void initialize(const std::vector<unsigned int>& data, GLenum usage);

	public:
		void bind() const;

		void unbind() const;

	private:
		unsigned int m_ID = -1;
	};
}