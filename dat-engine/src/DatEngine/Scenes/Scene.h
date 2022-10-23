#pragma once
#include "DatEngine/Graphics/Renderer/Renderer2D.h"

namespace dat
{
	class SceneHandler;

	class Scene
	{
	public:
		Scene() = default;
		virtual ~Scene() = default;

	public:
		virtual void onSceneEnter() { }

		virtual void onSceneLeave() { }

	public:
		virtual void handleInput(double dt) { }

		virtual void update(double dt) { }

		virtual void render(Renderer2D& renderer) { }

	public:
		void setHandler(SceneHandler* handler) { this->handler = handler; }

	protected:
		SceneHandler* handler = nullptr;
	};
}