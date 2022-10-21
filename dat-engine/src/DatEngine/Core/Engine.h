#pragma once
#include "pch.h"
#include "Window.h"
#include "DatEngine/Graphics/SpriteRenderer2D.h"

namespace dat
{
	class Engine
	{
	public:
		explicit Engine(int width, int height, const char* title);

	private:
		static void initializeGLFW();

		void initializeResources();

	public:
		void run();

	private:
		void processInput(double dt);

		void render();

		void update(double dt);

		void terminate();

	private:
		std::unique_ptr<Window> m_MainWindow;
		std::unique_ptr<SpriteRenderer2D> m_SpriteRenderer;

	private:
		int m_Width = 0, m_Height = 0;
	};
}