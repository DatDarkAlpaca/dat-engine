#include "pch.h"
#include "Engine.h"

#include "InputHandler.h"
#include "ResourceManager.h"

dat::Engine::Engine(int width, int height, const char* title)
	: m_Width(width), m_Height(height)
{
	initializeLogger();
	initializeGLFW();

	m_MainWindow = std::make_unique<Window>(width, height, title);
	m_MainWindow->setContext();

	if (glewInit() != GLEW_OK)
		DAT_CORE_CRITICAL("Failed to initialize GLEW.");
	else
		DAT_CORE_TRACE("Sucessfully initialized GLEW");

	m_MainWindow->setViewport(0, 0, width, height);
	initializeSystems();
}

void dat::Engine::initializeGLFW()
{
	if (glfwInit() != GLFW_TRUE)
	{
		DAT_CORE_CRITICAL("Failed to initialize GLFW.");
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

	DAT_CORE_TRACE("Sucessfully initialized GLFW");
}

void dat::Engine::initializeSystems()
{
	// Input:
	glfwSetKeyCallback(m_MainWindow.get()->window(), InputHandler::inputKeyCallback);

	// Renderer:
	m_Renderer = std::make_unique<Renderer>();
	m_Renderer->initialize();

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

	m_Renderer->setColor(glm::vec4(0.3, 0.3, 0.4, 1.0));
	m_Renderer->clear();

	m_SceneHandler->render(*m_Renderer.get());

	m_Renderer->executeCommands();

	glfwSwapBuffers(window);
}

void dat::Engine::update(double dt)
{
	m_SceneHandler->update(dt);
}

void dat::Engine::terminate()
{
	m_Renderer->shutdown();
	m_MainWindow->close();
}
