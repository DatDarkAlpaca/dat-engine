#pragma once
#include "pch.h"
#include "DatEngine/Graphics/Shader.h"

namespace dat
{
	class ShapeRenderer2D
	{
	public:
		explicit ShapeRenderer2D(const Shader& shader)
		{
			m_Shader = shader;
			initialize();
		}

		explicit ShapeRenderer2D() = default;

	private:
		void initialize()
		{
			// Quad:
			unsigned int quadVBO;

			float quadVertices[] = 
			{
				0.0f, 0.0f,
				0.0f, 1.0f,
				1.0f, 0.0f,

				0.0f, 1.0f,
				1.0f, 1.0f,
				1.0f, 0.0f
			};

			glGenVertexArrays(1, &m_QuadVAO);
			glGenBuffers(1, &quadVBO);

			glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

			glBindVertexArray(m_QuadVAO);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			// Triangle:
			unsigned int triangleVBO;

			float triangleVertices[] =
			{
				-0.5f, -0.5f,
				 0.5f, -0.5f,
				 0.0f,  0.5f
			};

			glGenVertexArrays(1, &m_TriangleVAO);
			glGenBuffers(1, &triangleVBO);

			glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

			glBindVertexArray(m_TriangleVAO);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

	public:
		void renderQuad(glm::vec2 position, glm::vec2 size, float rotationAngle, glm::vec3 color)
		{
			m_Shader.use();

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(position, 0.0f));

			model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
			model = glm::rotate(model, glm::radians(rotationAngle), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

			model = glm::scale(model, glm::vec3(size, 1.0));

			m_Shader.setMatrix4f("model", model);
			m_Shader.setVector3f("objColor", color);

			glBindVertexArray(m_QuadVAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}

		void renderTriangle(glm::vec2 position, glm::vec2 size, float rotationAngle, glm::vec3 color)
		{
			m_Shader.use();

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(position, 0.0f));

			model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
			model = glm::rotate(model, glm::radians(rotationAngle), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

			model = glm::scale(model, glm::vec3(size, 1.0));

			m_Shader.setMatrix4f("model", model);
			m_Shader.setVector3f("objColor", color);

			glBindVertexArray(m_TriangleVAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
		}

	public:
		void setShader(const Shader& shader)
		{
			m_Shader = shader;
			initialize();
		}

	private:
		unsigned int m_QuadVAO = -1, m_TriangleVAO = -1;
		Shader m_Shader = {};
	};
}