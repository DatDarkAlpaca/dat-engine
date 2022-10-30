#pragma once
#include "pch.h"
#include "Window.h"

#include "DatEngine/Graphics/Renderer.h"
#include "DatEngine/Scenes/SceneHandler.h"

namespace dat
{
	class Engine
	{
	public:
		explicit Engine(int width, int height, const char* title);
		virtual ~Engine() = default;

	private:
		static void initializeGLFW();

		void initializeSystems();

	public:
		void run();

	private:
		void processInput(double dt);

		void render();

		void update(double dt);

		void terminate();

	protected:
		std::unique_ptr<Window> m_MainWindow;
		std::unique_ptr<Renderer> m_Renderer;
		std::unique_ptr<SceneHandler> m_SceneHandler;

	protected:
		int m_Width = 0, m_Height = 0;
	};
}