#pragma once
#include "SpriteRenderer2D.h"
#include "ShapeRenderer2D.h"
#include "TextRenderer.h"

namespace dat
{
	class Renderer2D
	{
	public:
		Renderer2D()
		{
			m_SpriteRenderer = std::make_unique<SpriteRenderer2D>();
			m_ShapeRenderer = std::make_unique<ShapeRenderer2D>();
		}

	public:
		void initialize()
		{
			m_SpriteRenderer->setShader(ResourceManager::getShader("sprite"));
			m_ShapeRenderer->setShader(ResourceManager::getShader("default"));

			m_TextRenderer = std::make_unique<TextRenderer>(800, 600, "res/fonts/ocraext.ttf", 28);
		}

	public:
		void drawQuad(glm::vec2 position, glm::vec2 size, float rotationAngle = 0.f, glm::vec3 color = glm::vec3(1.f)) const
		{
			m_ShapeRenderer->renderQuad(position, size, rotationAngle, color);
		}

		void drawTriangle(glm::vec2 position, glm::vec2 size, float rotationAngle = 0.f, glm::vec3 color = glm::vec3(1.f)) const
		{
			m_ShapeRenderer->renderTriangle(position, size, rotationAngle, color);
		}

		void drawSprite(const Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(100.0f, 100.0f),
					    float rotationAngle = 0.0f, glm::vec3 color = glm::vec3(1.0f)) const
		{
			m_SpriteRenderer->render(texture, position, size, rotationAngle, color);
		}

		void drawText(std::string_view text, glm::vec2 position, float scale, glm::vec3 color = glm::vec3(1.0f)) const
		{
			m_TextRenderer->render(text, position, scale, color);
		}

	public:
		std::unique_ptr<SpriteRenderer2D> m_SpriteRenderer;
		std::unique_ptr<ShapeRenderer2D> m_ShapeRenderer;
		std::unique_ptr<TextRenderer> m_TextRenderer;
	};
}