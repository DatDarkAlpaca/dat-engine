#include "pch.h"
#include "SpriteRenderer2D.h"

dat::SpriteRenderer2D::SpriteRenderer2D(const Shader& shader)
{
	m_Shader = shader;
	initialize();
}

void dat::SpriteRenderer2D::setShader(const Shader& shader)
{
	m_Shader = shader;
	initialize();
}

void dat::SpriteRenderer2D::render(const Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotationAngle, glm::vec3 color)
{
	if (texture.width <= 0 || texture.height <= 0)
		return;

	m_Shader.use();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, glm::radians(rotationAngle), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(texture.width, texture.height, 1.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	m_Shader.setMatrix4f("model", model);
	m_Shader.setVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.bind();

	glBindVertexArray(m_QuadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void dat::SpriteRenderer2D::initialize()
{
	unsigned int VBO;
	float vertices[] =
	{
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &m_QuadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(m_QuadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}