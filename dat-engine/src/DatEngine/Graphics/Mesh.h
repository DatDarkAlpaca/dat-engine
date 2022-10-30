#pragma once
#include "pch.h"

namespace dat
{
	class Mesh
	{
	public:
		Mesh(float* vertices, size_t vertexCount, size_t dimensions = 2);
		Mesh(float* vertices, size_t vertexCount, int* indices, size_t elementCount, size_t dimensions = 2);
		~Mesh();

	public:
		void bind();

		void unbind();

	public:
		size_t getVertexCount() const { return m_VertexCount; }

		size_t getElementCount() const { return m_ElementCount; }

	private:
		uint32_t m_VertexCount = 0, m_ElementCount = 0;
		unsigned int m_VAO = -1, m_EBO = -1, m_PositionVBO = -1;
	};
}