#pragma once
#include "pch.h"
#include "Scene.h"

namespace dat
{
	class SceneHandler
	{
	public:
		bool exists(std::string_view sceneName) const
		{
			return m_Scenes.find(sceneName) != m_Scenes.end();
		}

		void addScene(std::string_view sceneName, std::shared_ptr<Scene> scene)
		{
			if (exists(sceneName))
			{
				DAT_CORE_WARN("Failed to insert a scene at '{}'. Scene already exists.", sceneName.data());
				return;
			}

			m_Scenes[sceneName] = std::move(scene);
		}

		void setScene(std::string_view sceneName)
		{
			if (m_CurrentScene)
				m_CurrentScene->onSceneLeave();

			m_CurrentScene = m_Scenes[sceneName];
			m_CurrentScene->onSceneEnter();
		}

	public:
		void handleInput(double dt)
		{
			if (m_CurrentScene)
				m_CurrentScene->handleInput(dt);
		}

		void update(double dt)
		{
			if (m_CurrentScene)
				m_CurrentScene->update(dt);
		}

		void render(Renderer2D& renderer)
		{
			if (m_CurrentScene)
				m_CurrentScene->render(renderer);
		}

	private:
		std::unordered_map<std::string_view, std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_CurrentScene;
	};
}