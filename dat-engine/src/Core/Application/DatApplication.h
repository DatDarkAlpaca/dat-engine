#pragma once
#include "API.h"
#include "Window/Window.h"
#include "Layer/LayerStack.h"
#include "Timestep/ITimestepHandler.h"

namespace dat
{
	class DAT_API DatApplication
	{
	public:
		DatApplication(int width, int height, const char* title);

		virtual ~DatApplication() = default;

	private:
		void initialize();

		void shutdown();

	public:
		void run();

	private:
		void onEvent(IEvent& event);

		void onRender();

	public:
		LayerStack& layers() { return m_LayerStack; }

		const Window& window() const { return m_Window; }

	private:
		LayerStack m_LayerStack;
		Window m_Window;

	private:
		ITimestepHandler* m_TimestepHandler;
	};
}
