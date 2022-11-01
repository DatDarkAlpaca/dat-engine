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

			camera = std::make_shared<OrthoCamera>(2.f, 0, 1000, 16/9);
		}

	public:
		void onSceneEnter() override
		{
			float vertices[] =
			{
				 0.5f,  0.5f,
				 0.5f, -0.5f,
				-0.5f, -0.5f,
				-0.5f,  0.5f,
			};

			int indices[] =
			{
				0, 3, 1,
				1, 3, 2
			};

			quadMesh = std::make_shared<Mesh>(vertices, 4, indices, 6);

			auto shader = ResourceManager::getShader("default");
			shader->use();

			shader->setMatrix4f("model", glm::mat4(1.0f));
		}

		void onSceneLeave() override
		{
		}

	public:
		void handleInput(double dt) override
		{
			// Camera zoom:
			float height = camera->getHeight();

			if (height <= 10.f && InputHandler::scrollOffset() < 0.f)
				camera->setHeight(height + 0.03f);

			if (height >= 2.f && InputHandler::scrollOffset() > 0.f)
				camera->setHeight(height - 0.03f);
		}

		void update(double dt) override 
		{
		}

		void render(Renderer& renderer) override
		{
			renderer.setWireframe(true);

			auto shader = ResourceManager::getShader("default");
			shader->use();
			shader->setMatrix4f("projection", camera->getProjectionMatrix());

			auto command = std::make_unique<RenderMesh>(quadMesh, shader);

			renderer.addCommand(std::move(command));
		}

	private:
		std::shared_ptr<Mesh> quadMesh;
		std::shared_ptr<OrthoCamera> camera;
	};
}