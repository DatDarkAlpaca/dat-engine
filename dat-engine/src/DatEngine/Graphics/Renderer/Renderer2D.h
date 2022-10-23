#pragma once
#include "SpriteRenderer2D.h"
#include "TextRenderer.h"

namespace dat
{
	class Renderer2D
	{
	public:
		Renderer2D()
		{
			m_SpriteRenderer = std::make_unique<SpriteRenderer2D>();
		}

	public:
		void initialize()
		{
			m_SpriteRenderer->setShader(ResourceManager::getShader("sprite"));

			m_TextRenderer = std::make_unique<TextRenderer>(800, 600, "res/fonts/ocraext.ttf", 28);
		}

	public:
		void drawSprite(const Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(100.0f, 100.0f),
					    float rotationAngle = 0.0f, glm::vec3 color = glm::vec3(1.0f))
		{
			m_SpriteRenderer->render(texture, position, size, rotationAngle, color);
		}

		void drawText(std::string_view text, glm::vec2 position, float scale, glm::vec3 color = glm::vec3(1.0f))
		{
			m_TextRenderer->render(text, position, scale, color);
		}

	private:
		std::unique_ptr<SpriteRenderer2D> m_SpriteRenderer;
		std::unique_ptr<TextRenderer> m_TextRenderer;
	};
}