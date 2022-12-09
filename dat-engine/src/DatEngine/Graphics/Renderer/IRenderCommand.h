#pragma once
#include "Graphics/Buffers/VertexArray.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Buffers/Buffer.h"

#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

namespace dat::graphics
{
	class IRenderCommand
	{
	public:
		virtual ~IRenderCommand() = default;

	public:
		virtual void execute() = 0;
	};

	class BasicRenderCommand : public IRenderCommand
	{
	public:
		BasicRenderCommand(Shader& shader, Texture& texture, glm::vec3 position, float angle, glm::vec3 size, glm::vec4 color)
			: m_Shader(shader), m_Texture(texture), m_Position(position), m_Angle(angle)
		{
			m_VAO.bind();

			float data[] = {
				0, 0, 0,
				0, size.y, 0,
				size.x, size.y, 0,
				size.x, 0, 0
			};

			float colors[] = {
				color.r, color.g, color.b, color.a,
				color.r, color.g, color.b, color.a,
				color.r, color.g, color.b, color.a,
				color.r, color.g, color.b, color.a
			};

			float uv[] = {
				0, 0,
				0, 1,
				1, 1,
				1, 0
			};

			m_VAO.addBuffer(new Buffer(data, 3 * sizeof(float), 3), 0);
			m_VAO.addBuffer(new Buffer(colors, 4 * sizeof(float), 4), 1);
			m_VAO.addBuffer(new Buffer(uv, 2 * sizeof(float), 2), 2);

			// IBO:
			GLushort indices[6] = {
				0, 1, 2,
				2, 3, 0
			};

			m_IBO = new IndexBuffer(indices, 6);
			m_IBO->bind();

			m_VAO.unbind();
		}

	public:
		void execute() final
		{
			m_Texture.bind();
			m_Shader.bind();
			
			m_VAO.bind();
			m_IBO->bind();

			m_Shader.setInteger("u_texture", 0);	// Sampler

			glm::mat4 model = glm::mat4(1.f);
			model = glm::translate(model, m_Position);
			model = glm::rotate(model, glm::radians(m_Angle), glm::vec3(0.f, 0.f, 1.f));

			m_Shader.setMatrix4f("u_model_matrix", model);

			glDrawElements(GL_TRIANGLES, m_IBO->getIndexCount(), GL_UNSIGNED_SHORT, nullptr);
		}

	private:
		VertexArray m_VAO;
		IndexBuffer* m_IBO;
		Shader& m_Shader;
		Texture& m_Texture;

	private:
		glm::vec3 m_Position;
		float m_Angle;
	};
}