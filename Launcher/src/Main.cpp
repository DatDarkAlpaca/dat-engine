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
			// Sprite Shader:
			ResourceManager::loadShader(
				"sprite",
				"res/shaders/sprite_vertex.glsl",
				"res/shaders/sprite_fragment.glsl"
			);

			// Sprite Shader Uniforms:
			glm::mat4 projection = glm::ortho(0.0f, (float)m_Width, (float)m_Height, 0.0f, -1.0f, 1.0f);

			Shader sprite = ResourceManager::getShader("sprite");
			sprite.use();
			sprite.setInteger("image", 0);
			sprite.setMatrix4f("projection", projection);

			// Text Shader:
			ResourceManager::loadShader(
				"text_shader",
				"res/shaders/text_vertex_shader.glsl",
				"res/shaders/text_fragment_shader.glsl"
			);

			// Renderer:
			m_Renderer->initialize();

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