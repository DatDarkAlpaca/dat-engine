#pragma once
#include "Common.hpp"

#include "Core/Assets/AssetLibrary.hpp"
#include "Core/Worker/WorkerPool.hpp"
#include "Core/View/ViewSystem.hpp"

#include "Platform/Platform.hpp"

namespace dat
{
	class DatEngine
	{
	public:
		DatEngine(const std::filesystem::path& configFilePath = "engine-config.json");

	public:
		void Run();

	private:
		void Shutdown();

	public:
		void AddView(dat_unique<View> view);

	private:
		void OnEngineStartup();

		void OnRender();

		void OnRenderGUI();

		void OnUpdate();

		void OnEvent(Event& event);

		void OnEngineShutdown();

	public:
		AssetLibrary& GetAssetLibrary() { return g_AssetLibrary; }

		ViewSystem& GetViewSystem() { return g_ViewSystem; }

		platform::Window& GetWindow() { return g_Window; }

		WorkerPool& GetWorkerPool() { return g_WorkerPool; }

	private:
		AssetLibrary g_AssetLibrary;
		ViewSystem g_ViewSystem;
		WorkerPool g_WorkerPool;

		platform::Window g_Window;

	private:
		bool m_Initialized = false;
	};
}