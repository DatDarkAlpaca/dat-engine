#pragma once
#include "Shader.h"
#include "Texture.h"

namespace dat
{
	class SpriteRenderer2D
	{
	public:
		explicit SpriteRenderer2D(const Shader& shader);

	private:
		void initialize();

	public:
		void drawSprite(const Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(100.0f, 100.0f),
					    float rotationAngle = 0.0f, glm::vec3 color = glm::vec3(1.0f));

	private:
		unsigned int m_QuadVAO = 0;
		Shader m_Shader = {};
	};
}