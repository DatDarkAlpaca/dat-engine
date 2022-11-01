#pragma once
#include <DatEngine.h>
#include "PhysicsScene.h"

namespace dat
{
	struct Client : public dat::Engine
	{
	public:
		Client(int width, int height, const char* title);

	private:
		void initializeResources();

		void initializeScenes();
	};
}