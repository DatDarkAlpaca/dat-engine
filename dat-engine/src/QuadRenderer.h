#pragma once
#include "API.h"
#include "Graphics/Shader.h"
#include "Graphics/VertexArray.h"

namespace dat
{
	class QuadRenderer
	{
	public:
		QuadRenderer(Shader* shader) 
			: m_Shader(shader) 
		{ 
			initialize(); 
		}

		QuadRenderer() = default;

	public:
		void setShader(Shader* shader) { m_Shader = shader; }

		void initialize()
		{
			m_VAO.bind();

			VertexBuffer vbo ({
				 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
				 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,

				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
				-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
				 0.5f,  0.5f, 0.0f, 1.0f, 1.0f
			});

			{
				VertexAttributes attributes;
				attributes.addAttribute(0, 3, AttributeType::FLOAT, GL_FALSE);
				attributes.addAttribute(1, 2, AttributeType::FLOAT, GL_FALSE);
				m_VAO.enableAttributes(attributes);
			}

			m_VAO.unbind();
		}

	public:
		void drawQuad(Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
		{
			m_Shader->bind();

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(position, 1.f));

			model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
			model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

			model = glm::scale(model, glm::vec3(size, 1.0f));

			m_Shader->setMatrix4f("u_model", model);
			m_Shader->setVector3f("u_color", color);

			texture.bind();

			m_VAO.bind();
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

	private:
		Shader* m_Shader = nullptr;
		VertexArray m_VAO;
	};
}