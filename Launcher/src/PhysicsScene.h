#pragma once
#include <DatEngine.h>

namespace dat
{
	class PhysicsScene final : public Scene
	{
	public:
		PhysicsScene(SceneHandler* handler)
		{
			setHandler(handler);
		}

	public:
		void onSceneEnter() override
		{
			float scale = 0.5;
			float size = 128 * scale;
			float offset = 5;

			GameObject object1(glm::vec2(0.f, 0.f), glm::vec2(scale, scale), ResourceManager::getTexture("square"));
			GameObject object2(glm::vec2(0, size + offset), glm::vec2(scale, scale), ResourceManager::getTexture("square"));
			GameObject object3(glm::vec2(size + offset, 0), glm::vec2(scale, scale), ResourceManager::getTexture("square"));
			GameObject object4(glm::vec2(size + offset, size + offset), glm::vec2(scale, scale), ResourceManager::getTexture("square"));
			addObject(object1);
			addObject(object2);
			addObject(object3);
			addObject(object4);

			for (auto& obj : m_GameObjects)
				obj->mass = 0.001f;
		}

		void onSceneLeave() override
		{
		}

	public:
		void handleInput(double dt) override
		{
			if (InputHandler::isKeyPressed(GLFW_KEY_SPACE))
			{
				enableGravity = !enableGravity;
			}
		}

		void update(double dt) override 
		{
			for (const auto& object : m_GameObjects)
			{
				if (enableGravity)
				{
					object->force += object->mass * gravity * -1.f;

					object->velocity += object->force / object->mass;
					object->position += object->velocity * (float)dt;

					object->force = glm::vec3(0.f);
				}
			}
		}

		void render(SpriteRenderer2D& renderer) override
		{
			for (const auto& object : m_GameObjects)
				object->draw(renderer);
		}

	private:
		int addObject(const GameObject& object)
		{
			static int id = 0;
			m_GameObjects.push_back(std::make_unique<GameObject>(object));

			return id++;
		}

		void removeObject(int id)
		{

		}

	private:
		std::vector<std::unique_ptr<GameObject>> m_GameObjects;

	private:
		bool enableGravity = false;
		glm::vec2 gravity = glm::vec2(0, -9.871f);
	};
}