#include "pch.hpp"
#include "Engine.hpp"

#include "Graphics/GraphicsSystem.hpp"
#include "Core/Config/JsonReader.hpp"
#include "Core/Config/ConfigData.hpp"
#include "Platform/Platform.hpp"

namespace dat
{
	DatEngine::DatEngine(const std::filesystem::path& configFilePath)
	{
		// Config System:
		JsonReader configReader(configFilePath);
		auto configData = configReader.Parse<ConfigData>();

		// Graphics System:
		platform::gl::SetupOpenGLWindowing(g_Window, configData.windowProperties, configData.graphicsSpecification);
		g_Window.SetEventCallback(BIND(&DatEngine::OnEvent, this));

		m_Initialized = true;
	}

	void DatEngine::Run()
	{
		OnEngineStartup();

		if (!m_Initialized)
			DAT_LOG_CRITICAL("Failed to initialize the required systems.");

		while (g_Window.IsOpen())
		{
			g_Window.PollEvents();
			g_WorkerPool.PollTasks();

			OnUpdate();

			OnRender();

			OnRenderGUI();
		}

		Shutdown();
	}

	void DatEngine::Shutdown()
	{
		OnEngineShutdown();

		g_Window.Shutdown();
	}

	void DatEngine::AddView(dat_unique<View> view)
	{
		view->SetEngine(this);
		g_ViewSystem.Add(std::move(view));
	}

	void DatEngine::OnEngineStartup()
	{
		for (const auto& view : g_ViewSystem)
			view->OnEngineStartup();
	}

	void DatEngine::OnRender()
	{
		for (const auto& view : g_ViewSystem)
			view->OnRender();
	}

	void DatEngine::OnRenderGUI()
	{
		for (const auto& view : g_ViewSystem)
			view->OnRenderGUI();
	}

	void DatEngine::OnUpdate()
	{
		for (const auto& view : g_ViewSystem)
			view->OnUpdate();
	}

	void DatEngine::OnEvent(Event& event)
	{
		for (const auto& view : g_ViewSystem)
			view->OnEvent(event);
	}

	void DatEngine::OnEngineShutdown()
	{
		for (const auto& view : g_ViewSystem)
			view->OnEngineShutdown();
	}
}