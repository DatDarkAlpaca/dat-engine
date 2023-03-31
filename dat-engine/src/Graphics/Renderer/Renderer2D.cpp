#include "pch.h"
#include "Renderer2D.h"

#include "Graphics/OpenGL/IndexBuffer.h"
#include "Graphics/OpenGL/VertexArray.h"
#include "Graphics/OpenGL/VertexBuffer.h"
#include "Graphics/OpenGL/Factories/ShaderFactory.h"

namespace dat
{
	struct Renderer2DDescriptor
	{
		dat_unique<Shader> flatQuadShader;
		dat_unique<Shader> texturedQuadShader;

		dat_unique<VertexArray> quadVAO = nullptr;
	};

	static Renderer2DDescriptor s_Descriptor;

	void Renderer2D::initialize()
	{
		// Quad Shader:
		s_Descriptor.flatQuadShader = std::make_unique<Shader>(createShader(
			"res/shader/flat_quad_vert.glsl",
			"res/shader/flat_quad_frag.glsl"
		));

		s_Descriptor.texturedQuadShader = std::make_unique<Shader>(createShader(
			"res/shader/textured_quad_vert.glsl",
			"res/shader/textured_quad_frag.glsl"
		));

		s_Descriptor.texturedQuadShader->bind();
		s_Descriptor.texturedQuadShader->setInteger("u_texture", 0);

		// Quad VAO:
		s_Descriptor.quadVAO = std::make_unique<VertexArray>();
		s_Descriptor.quadVAO->bind();
		
		VertexBuffer vbo({
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		});

		IndexBuffer ibo({
			0, 1, 2, 2, 3, 0
		});

		{
			VertexAttributes attributes;
			attributes.addAttribute(0, 3, AttributeType::FLOAT, false); // Position
			attributes.addAttribute(1, 2, AttributeType::FLOAT, false); // UVs
			s_Descriptor.quadVAO->enableAttributes(attributes);
		}

		vbo.unbind();
		s_Descriptor.quadVAO->unbind();
	}

	void Renderer2D::beginScene(const ICamera& camera)
	{
		s_Descriptor.flatQuadShader->bind();
		s_Descriptor.flatQuadShader->setMatrix4f("u_view", camera.view());
		s_Descriptor.flatQuadShader->setMatrix4f("u_projection", camera.projection());

		s_Descriptor.texturedQuadShader->bind();
		s_Descriptor.texturedQuadShader->setMatrix4f("u_view", camera.view());
		s_Descriptor.texturedQuadShader->setMatrix4f("u_projection", camera.projection());
	}

	// Flat Quad:
	void Renderer2D::submitQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float rotation)
	{
		s_Descriptor.flatQuadShader->bind();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);
		model = glm::scale(model, glm::vec3(size, 1.0f));
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.f, 0.f, 1.f));

		s_Descriptor.flatQuadShader->setMatrix4f("u_model", model);
		s_Descriptor.flatQuadShader->setVector4f("u_color", color);

		s_Descriptor.quadVAO->bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}

	void Renderer2D::submitQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float rotation)
	{
		submitQuad(glm::vec3(position, 0.0), size, color, rotation);
	}

	// Textured Quad:
	void Renderer2D::submitQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float rotation, dat_shared<Texture2D> texture)
	{
		s_Descriptor.texturedQuadShader->bind();
		
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);
		model = glm::scale(model, glm::vec3(size, 1.0f));
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.f, 0.f, 1.f));

		s_Descriptor.texturedQuadShader->setMatrix4f("u_model", model);
		s_Descriptor.flatQuadShader->setVector4f("u_color", color);
		
		texture->bind(0);
		s_Descriptor.quadVAO->bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}

	void Renderer2D::submitQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float rotation, dat_shared<Texture2D> texture)
	{
		submitQuad(glm::vec3(position, 0.0), size, color, rotation, texture);
	}
}