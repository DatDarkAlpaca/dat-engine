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
}

void dat::Client::initializeScenes()
{
	sceneHandler->addScene("physics", std::make_unique<PhysicsScene>(sceneHandler.get()));
	sceneHandler->setScene("physics");
}
