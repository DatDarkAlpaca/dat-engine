#pragma once
#include "pch.h"
#include "VertexAttributes.h"

namespace dat
{
	class VertexArray
	{
	public:
		VertexArray();

		~VertexArray();

	public:
		void enableAttributes(const VertexAttributes& attributes);

	public:
		void bind() const { glBindVertexArray(m_ID); }

		void unbind() const { glBindVertexArray(0); }

	private:
		unsigned int m_ID = -1;
	};
}