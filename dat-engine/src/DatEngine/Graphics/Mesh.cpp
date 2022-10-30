#include "pch.h"
#include "Mesh.h"

dat::Mesh::Mesh(float* vertices, size_t vertexCount, size_t dimensions)
	: m_VertexCount(vertexCount)
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_PositionVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * dimensions * sizeof(float), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, dimensions, GL_FLOAT, GL_FALSE, dimensions * sizeof(float), (void*)0);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

dat::Mesh::Mesh(float* vertices, size_t vertexCount, int* indices, size_t elementCount, size_t dimensions)
	: Mesh(vertices, vertexCount, dimensions)
{
	m_ElementCount = elementCount;

	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementCount * sizeof(int), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

dat::Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_PositionVBO);

	if (m_EBO != -1)
		glDeleteBuffers(1, &m_EBO);

	glDeleteVertexArrays(1, &m_VAO);
}

void dat::Mesh::bind()
{
	glBindVertexArray(m_VAO);
	glEnableVertexAttribArray(0);
}

void dat::Mesh::unbind()
{
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}
