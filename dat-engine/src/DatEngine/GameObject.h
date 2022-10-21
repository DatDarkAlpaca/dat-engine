#pragma once
#include "pch.h"
#include "Graphics/Texture.h"
#include "Graphics/SpriteRenderer2D.h"

namespace dat
{
	class GameObject
	{
	public:
		GameObject()
		{

		}

		GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f))
			:	position(pos),
				size(size),
				sprite(sprite),
				color(color),
				velocity(velocity)
		{

		}

	public:
		virtual void draw(SpriteRenderer2D& renderer)
		{
			renderer.drawSprite(sprite, position, size, angle, color);
		}

	public:
		glm::vec2 position = glm::vec2(0.f), size = glm::vec2(1.f), velocity = glm::vec2(0.f);
		glm::vec3 color = glm::vec3(1.f);
		float angle = 0.f;
		bool isSolid = true, isDestroyed = false;

		Texture2D sprite;
	};
}