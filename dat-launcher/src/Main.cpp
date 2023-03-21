#include <DatEngine.h>

using namespace dat;

class Layer : public ILayer
{
public:
	Layer(DatApplication* application)
		: ILayer(application), camera(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f)
	{
		m_Shaders.add("quad", std::make_shared<Shader>("res/quad_vertex.glsl", "res/quad_frag.glsl"));
		Shader* shader = m_Shaders.get("quad");
	
		m_Textures.add("texture", std::make_shared<Texture2D>("res/brick.jpg"));
		
		renderer = new QuadRenderer(shader);
	}

public:
	void onUpdate() override
	{
		camera.setPosition({ x, y, 0.f });
		camera.computeViewMatrix();

		renderer->shader()->bind().setMatrix4f("u_projection", camera.projection());
		renderer->shader()->bind().setMatrix4f("u_view", camera.view());
	}

	void onRender() override
	{
		Texture2D* texture = m_Textures.get("texture");
		renderer->drawQuad(*texture, { 100, 100 }, { 150.f, 150.f }, 0, { 0.1f, 0.4f, 0.7f });
	}

	void onEvent(IEvent& event) override
	{
		EventDispatcher di(event);
		di.dispatch<MousePressedEvent>([&](MousePressedEvent& eve) {
			DAT_CORE_CRITICAL("{}", debugMods(eve.mods));
			return false;
		});
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
