#pragma once
#include <DatEngine.h>

namespace dat
{
	class PhysicsScene final : public Scene
	{
	public:
		PhysicsScene(SceneHandler* handler)
		{
		}

	public:
		void onSceneEnter() override
		{
			DAT_CORE_TRACE("hello");
		}

		void onSceneLeave() override
		{
		}

	public:
		void handleInput(double dt) override
		{
		}

		void update(double dt) override 
		{
		}

		void render(Renderer& renderer) override
		{
		}
	};
}