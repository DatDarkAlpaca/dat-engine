#pragma once
#include "pch.h"
#include "VertexAttributes.h"

namespace dat
{
	class DAT_API VertexArray
	{
	public:
		VertexArray();

		~VertexArray();

	public:
		void enableAttributes(const VertexAttributes& attributes);

	public:
		void bind() const;

		void unbind() const;

	private:
		unsigned int m_ID = -1;
	};
}