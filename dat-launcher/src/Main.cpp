#include <DatEngine.h>

using namespace dat;

class Layer : public ILayer
{
public:
	Layer()
		: camera(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f)
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
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<KeyPressedEvent>([&](KeyPressedEvent& event) {
			if (event.key == GLFW_KEY_W)
				y -= 10.f;
			if (event.key == GLFW_KEY_S)
				y += 10.f;
			if (event.key == GLFW_KEY_A)
				x -= 10.f;
			if (event.key == GLFW_KEY_D)
				x += 10.f;
			return true;
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
		layers().addLayer(new Layer());
	}

public:

};

int main()
{
	auto c = Client(800, 600, "Dat Engine");
	c.run();
}
