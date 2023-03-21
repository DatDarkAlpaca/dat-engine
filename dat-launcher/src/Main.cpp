#include <DatEngine.h>

using namespace dat;

class Layer : public ILayer
{
public:
	Layer(DatApplication* application)
		: ILayer(application), camera(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f)
	{
		auto shader = m_Shaders.add("quad", std::make_shared<Shader>("res/quad_vertex.glsl", "res/quad_frag.glsl"));
	
		m_Textures.add("texture", std::make_shared<Texture2D>("res/brick.jpg"));

		renderer = new QuadRenderer(shader.get());
	}

public:
	void onUpdate(Timestep dt) override
	{
		DAT_CORE_CRITICAL("{}", dt.timestep());

		camera.setPosition({ x, y, 0.f });
		camera.computeViewMatrix();

		renderer->shader()->bind().setMatrix4f("u_projection", camera.projection());
		renderer->shader()->bind().setMatrix4f("u_view", camera.view());
	}

	void onRender() override
	{
		auto texture = m_Textures.get("texture");
		renderer->drawQuad(*texture.get(), {100, 100}, {150.f, 150.f}, 0, {0.1f, 0.4f, 0.7f});
	}

private:
	float x = 0, y = 0;
	QuadRenderer* renderer = nullptr;
	ResourceHolder<Shader> m_Shaders;
	ResourceHolder<Texture2D> m_Textures;
	OrthoCamera camera;
};

class Client : public DatApplication
{
public:
	Client(int width, int height, const char* title)
		: DatApplication(width, height, title)
	{
		layers().addLayer(new Layer(this));
	}

public:

};

int main()
{
	auto c = Client(800, 600, "Dat Engine");
	c.run();
}
