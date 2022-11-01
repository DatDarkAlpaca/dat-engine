#include "pch.h"
#include "Client.h"

dat::Client::Client(int width, int height, const char* title)
	: dat::Engine(width, height, title)
{
	initializeResources();

	initializeScenes();
}

void dat::Client::initializeResources()
{
	glm::mat4 projection = glm::ortho(0.0f, (float)m_Width, (float)m_Height, 0.0f, -1.0f, 1.0f);

	// Default Shader:
	ResourceManager::loadShader(
		"default",
		"res/shaders/vertex.glsl",
		"res/shaders/fragment.glsl"
	);

	Shader defaultShader = ResourceManager::getShader("default")->use();
	//defaultShader.setMatrix4f("projection", projection);

	// Sprite Shader:
	ResourceManager::loadShader(
		"sprite",
		"res/shaders/sprite_vertex.glsl",
		"res/shaders/sprite_fragment.glsl"
	);

	// Sprite Shader Uniforms:
	Shader sprite = ResourceManager::getShader("sprite")->use();
	sprite.setInteger("image", 0);
	sprite.setMatrix4f("projection", projection);

	// Text Shader:
	ResourceManager::loadShader(
		"text_shader",
		"res/shaders/text_vertex_shader.glsl",
		"res/shaders/text_fragment_shader.glsl"
	);

	// Textures:
	ResourceManager::loadTexture("square", "res/textures/square.png", true);
}

void dat::Client::initializeScenes()
{
	m_SceneHandler->addScene("physics", std::make_shared<PhysicsScene>(m_SceneHandler.get()));
	m_SceneHandler->setScene("physics");
}
