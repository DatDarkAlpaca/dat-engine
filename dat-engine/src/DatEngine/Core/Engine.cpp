#include "pch.h"
#include "Engine.h"

#include "InputHandler.h"
#include "ResourceManager.h"

dat::Engine::Engine(int width, int height, const char* title)
	: m_Width(width), m_Height(height)
{
	initializeLogger();

	mainWindow = std::make_unique<Window>(width, height, title);
	mainWindow->setContext();

	initializeSystems();
}

void dat::Engine::initializeSystems()
{
	// Input:
	glfwSetKeyCallback(mainWindow.get()->window(), InputHandler::inputKeyCallback);
	glfwSetScrollCallback(mainWindow.get()->window(), InputHandler::scrollCallback);

	// Renderer:
	renderer = std::make_unique<Renderer>();
	renderer->initialize(mainWindow, m_Width, m_Height);

	// Scene Handler:
	sceneHandler = std::make_unique<SceneHandler>();
}

void dat::Engine::run()
{
	auto window = mainWindow.get()->window();

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

	sceneHandler->handleInput(dt);
}

void dat::Engine::render()
{
	auto window = mainWindow.get()->window();

	sceneHandler->render(*renderer.get());

	glfwSwapBuffers(window);
}

void dat::Engine::update(double dt)
{
	sceneHandler->update(dt);
}

void dat::Engine::terminate()
{
	renderer->shutdown();
	mainWindow->close();
}
