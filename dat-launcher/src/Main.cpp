#include <DatEngine.h>

using namespace dat;

class Layer : public ILayer
{
public:
	Layer(DatApplication* app) : ILayer(app) 
	{
		glClearColor(0.08f, 0.08f, 0.08f, 1.0);
		m_Camera = new OrthoCamera(0.f, 800.f, 600.f, 0.f, -10.f, 100.f);

		texture = std::make_shared<Texture2D>("res/brick.jpg");
	}

	void onUpdate(Timestep dt) override
	{
		m_Camera->onUpdate(dt);
	}

	void onRender() override
	{
		Renderer2D::beginScene(*m_Camera);
		Renderer2D::submitQuad({ 100.f, 100.f }, { 150.f, 150.f }, { 0.6f, 0.45f, 0.6f, 1.f }, 45.f, texture);
	}

private:
	dat_shared<Texture2D> texture;
	OrthoCamera* m_Camera;
};

class Client : public DatApplication
{
public:
	Client(int width, int height, const char* title)
		: DatApplication(width, height, title)
	{
		layers().addLayer(new Layer(this));
	}
};

int main()
{
	auto c = Client(800, 600, "Dat Engine");
	c.run();
}
