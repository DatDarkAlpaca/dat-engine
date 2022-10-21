#include "pch.h"
#include "Engine.h"

#include "InputHandler.h"
#include "ResourceManager.h"

dat::Engine::Engine(int width, int height, const char* title)
	: m_Width(width), m_Height(height)
{
	initializeGLFW();

	m_MainWindow = std::make_unique<Window>(width, height, title);
	m_MainWindow->setContext();

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "[Error]: Failed to initialize GLEW.\n";
	}

	m_MainWindow->setViewport(0, 0, width, height);

	initializeResources();
}

void dat::Engine::initializeGLFW()
{
	if (glfwInit() != GLFW_TRUE)
	{
		std::cerr << "Failed to initialize GLFW\n";
		glfwTerminate();
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void dat::Engine::initializeResources()
{
	// Input:
	glfwSetKeyCallback(m_MainWindow.get()->window(), InputHandler::inputKeyCallback);

	// Shader:
	ResourceManager::loadShader(
		"sprite",
		"res/shaders/vertex_shader.glsl",
		"res/shaders/fragment_shader.glsl"
	);

	// Projection Matrix:
	glm::mat4 projection = glm::ortho(0.0f, (float)m_Width, (float)m_Height, 0.0f, -1.0f, 1.0f);

	ResourceManager::getShader("sprite").use().setInteger("image", 0);
	ResourceManager::getShader("sprite").setMatrix4f("projection", projection);

	// Renderer:
	m_SpriteRenderer = std::make_unique<SpriteRenderer2D>(ResourceManager::getShader("sprite"));

	// Textures:
	ResourceManager::loadTexture("square", "res/textures/square.png", true);

	// Scene Handler:
	m_SceneHandler = std::make_unique<SceneHandler>();
}

void dat::Engine::run()
{
	auto window = m_MainWindow.get()->window();

	double deltaTime = 0., lastFrame = 0.;
	while (!glfwWindowShouldClose(window))
	{
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Events:
		processInput(deltaTime);

		// Update:
		update(deltaTime);

		// Render:
		render();
	}

	terminate();
}

void dat::Engine::processInput(double dt)
{
	glfwPollEvents();

	m_SceneHandler->handleInput(dt);
}

void dat::Engine::render()
{
	auto window = m_MainWindow.get()->window();

	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_SceneHandler->render(*m_SpriteRenderer.get());

	glfwSwapBuffers(window);
}

void dat::Engine::update(double dt)
{
	m_SceneHandler->update(dt);
}

void dat::Engine::terminate()
{
	m_MainWindow->close();
}
