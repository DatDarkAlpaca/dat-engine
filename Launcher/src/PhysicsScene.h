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
		}

		void onSceneLeave() override
		{
		}

	public:
		void handleInput(double dt) override
		{
		}

		void update(double dt) override 
		{
		}

		void render(Renderer& renderer) override
		{
			renderer.setWireframe(true);

			auto shader = ResourceManager::getShader("default");
			
			auto command = std::make_unique<RenderMesh>(quadMesh, shader);

			renderer.addCommand(std::move(command));
		}

	private:
		std::shared_ptr<Mesh> quadMesh;
	};
}