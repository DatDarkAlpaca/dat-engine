#include <DatEngine.h>

using namespace dat;

class Layer : public ILayer
{
public:
	Layer(DatApplication* application)
		: ILayer(application), 
		// camera(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f)
		camera(45, 800.f, 600.f, 0.1f, 1000.f)
	{
		auto shader = m_Shaders.add("quad", std::make_shared<Shader>("res/quad_vertex.glsl", "res/quad_frag.glsl"));
		m_Shaders.add("cube", std::make_shared<Shader>("res/vertex.glsl", "res/frag.glsl"));

		m_Textures.add("texture", std::make_shared<Texture2D>("res/brick.jpg"));

		renderer = new QuadRenderer(shader.get());
		

		{
			vao.bind();

			VertexBuffer vbo({
				-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
				 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
				 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
				-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

				-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

				 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
				 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
				 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
				 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
			}, GL_STATIC_DRAW);

			VertexAttributes attrib;
			attrib.addAttribute(0, 3, AttributeType::FLOAT, false);
			attrib.addAttribute(1, 2, AttributeType::FLOAT, false);

			vao.enableAttributes(attrib);

			vao.unbind();
		}
	}

public:
	void onUpdate(Timestep dt) override
	{
		//if(camera.clickedIn)

		camera.onUpdate(dt);

		renderer->shader()->bind().setMatrix4f("u_projection", camera.projection());
		renderer->shader()->bind().setMatrix4f("u_view", camera.view());
	
		auto shader = m_Shaders.get("cube");
		shader->bind();
		shader->setMatrix4f("u_projection", camera.projection());
		shader->setMatrix4f("u_view", camera.view());
	}

	void onRender() override
	{
		auto texture = m_Textures.get("texture");
		renderer->drawQuad(*texture.get(), {100, 100}, {150.f, 150.f}, 0, {0.1f, 0.4f, 0.7f});

		glm::mat4 model;
		//model = glm::scale(model, glm::vec3(5.f, 5.f, 5.f));
		//model = glm::translate(model, glm::vec3(100.f, 100.f, 0.f));
		
		auto shader = m_Shaders.get("cube");
		shader->bind();
		//shader->setMatrix4f("u_model", model);

		vao.bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	void onEvent(IEvent& event) override
	{
		camera.onEvent(event);
	}

private:
	VertexArray vao;

	float x = 0, y = 0;
	QuadRenderer* renderer = nullptr;
	ResourceHolder<Shader> m_Shaders;
	ResourceHolder<Texture2D> m_Textures;
	PerspectiveCamera camera;
};

class Client : public DatApplication
{
public:
	Client(int width, int height, const char* title)
		: DatApplication(width, height, title)
	{
		glEnable(GL_DEPTH_TEST);
		layers().addLayer(new Layer(this));
		glfwSetInputMode(window().window(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}

public:

};

int main()
{
	auto c = Client(800, 600, "Dat Engine");
	c.run();
}
