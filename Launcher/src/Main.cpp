#include <DatEngine.h>
#include "PhysicsScene.h"

namespace dat
{
	struct Client : public dat::Engine
	{
	public:
		Client(int width, int height, const char* title) 
			: dat::Engine(width, height, title)
		{
			initializeResources();

			initializeScenes();
		}

	private:
		void initializeResources()
		{
			// Shader:
			ResourceManager::loadShader(
				"sprite",
				"res/shaders/vertex_shader.glsl",
				"res/shaders/fragment_shader.glsl"
			);

			// Shader Uniforms:
			glm::mat4 projection = glm::ortho(0.0f, (float)m_Width, (float)m_Height, 0.0f, -1.0f, 1.0f);

			Shader sprite = ResourceManager::getShader("sprite");
			sprite.use();
			sprite.setInteger("image", 0);
			sprite.setMatrix4f("projection", projection);

			// Renderer:
			m_SpriteRenderer->setShader(sprite);

			// Textures:
			ResourceManager::loadTexture("square", "res/textures/square.png", true);
		}

		void initializeScenes()
		{
			m_SceneHandler->addScene("physics", std::make_shared<PhysicsScene>(m_SceneHandler.get()));
			m_SceneHandler->setScene("physics");
		}
	};
}

int main()
{
	dat::Client engine(800, 600, "Default Title");
	engine.run();
}