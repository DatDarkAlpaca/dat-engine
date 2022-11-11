#include "pch.h"
#include "Engine.h"

#include "InputHandler.h"
#include "ResourceManager.h"

dat::Engine::Engine(int width, int height, const char* title)
	: m_Width(width), m_Height(height)
{
	initializeLogger();

	m_MainWindow = std::make_unique<Window>(width, height, title);
	m_MainWindow->setContext();

	initializeSystems();
}

void dat::Engine::initializeSystems()
{
	// Input:
	glfwSetKeyCallback(m_MainWindow.get()->window(), InputHandler::inputKeyCallback);
	glfwSetScrollCallback(m_MainWindow.get()->window(), InputHandler::scrollCallback);

	// Renderer:
	m_Renderer = std::make_unique<Renderer>();
	m_Renderer->initialize(m_MainWindow, m_Width, m_Height);

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

	m_SceneHandler->render(*m_Renderer.get());

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
