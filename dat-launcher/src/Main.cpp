#include <DatEngine.h>

using namespace dat;

class Layer : public ILayer
{
public:
	Layer()
	{
		m_Shaders.add("quad", std::make_shared<Shader>("res/quad_vertex.glsl", "res/quad_frag.glsl"));
		Shader* shader = m_Shaders.get("quad");
	
		renderer = new QuadRenderer(shader);
	}

public:
	void onRender() override
	{
		renderer->drawQuad({ 100.f, 100.f }, { 50.f, 50.f }, 0, { 0.1f, 0.4f, 0.7f });
	}

private:
	QuadRenderer* renderer = nullptr;
	ResourceHolder<Shader> m_Shaders;
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
