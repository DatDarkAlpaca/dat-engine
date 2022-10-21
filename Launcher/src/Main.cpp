#include <DatEngine.h>
#include "PhysicsScene.h"

namespace dat
{
	struct Client : public dat::Engine
	{
	public:
		Client()
			: dat::Engine(800, 600, "Default Title")
		{
			m_SceneHandler->addScene("physics", std::make_shared<PhysicsScene>(m_SceneHandler.get()));
			m_SceneHandler->setScene("physics");
		}
	};
}

int main()
{
	dat::Client engine;
	engine.run();
}