#include <DatEngine.h>

using namespace dat;

class Layer : public ILayer
{
public:
	Layer()
	{
		m_Shaders.add("quad", std::make_shared<Shader>("res/quad_vertex.glsl", "res/quad_frag.glsl"));
		Shader* shader = m_Shaders.get("quad");
	
		m_Textures.add("texture", std::make_shared<Texture2D>("res/brick.jpg"));
		
		renderer = new QuadRenderer(shader);
	}

public:
	void onRender() override
	{
		Texture2D* texture = m_Textures.get("texture");
		renderer->drawQuad(*texture, { x, y }, { 150.f, 150.f }, 0, { 0.1f, 0.4f, 0.7f });
	}

	void onEvent(IEvent& event) override
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<MouseMoveEvent>([&](MouseMoveEvent& mousePressedEvent) {
			x = mousePressedEvent.x;
			y = mousePressedEvent.y;
			return true;
		});
	}

private:
	float x, y;
	QuadRenderer* renderer = nullptr;
	ResourceHolder<Shader> m_Shaders;
	ResourceHolder<Texture2D> m_Textures;
};

class Client : public DatApplication
{
public:
	Client(int width, int height, const char* title)
		: DatApplication(width, height, title)
	{
		layers().addLayer(new Layer());
	}

public:

};

int main()
{
	auto c = Client(800, 600, "Dat Engine");
	c.run();
}
