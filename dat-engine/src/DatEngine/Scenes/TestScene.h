#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Core/InputHandler.h"
#include "Core/ResourceManager.h"

namespace dat
{
	class TestScene final : public Scene
	{
	public:
		TestScene(SceneHandler* handler)
		{
			setHandler(handler);
		}

	public:
		void onSceneEnter() override
		{
			player = new GameObject();
			player->position = glm::vec2(0.f);
			player->size = glm::vec2(1.f);
			player->sprite = ResourceManager::getTexture("square");
		}

		void onSceneLeave() override
		{
			delete player;
		}

	public:
		void handleInput(double dt) override 
		{
			float velocity = 500.f * (float)dt;

			if (InputHandler::isKeyPressed(GLFW_KEY_A))
			{
				if (player->position.x >= 0.0f)
					player->position.x -= velocity;
			}

			if (InputHandler::isKeyPressed(GLFW_KEY_D))
				player->position.x += velocity;

			if (InputHandler::isKeyPressed(GLFW_KEY_W))
			{
				if (player->position.y >= 0)
					player->position.y -= velocity;
			}

			if (InputHandler::isKeyPressed(GLFW_KEY_S))
				player->position.y += velocity;
		}

		void update(double dt) override { }

		void render(SpriteRenderer2D& renderer) override
		{
			player->draw(renderer);
		}

	private:
		GameObject* player = nullptr;
	};
}