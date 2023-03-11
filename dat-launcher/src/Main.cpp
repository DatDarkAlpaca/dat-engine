#include <DatEngine.h>

using namespace dat;

class Layer : public ILayer
{
public:
	Layer()
	{
		m_Shaders.add("main", std::make_shared<Shader>("res/vertex.glsl", "res/frag.glsl"));

		vao.bind();

		VertexBuffer vbo({
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.0f, 0.0f
		});

		{
			VertexAttributes attributes;
			attributes.addAttribute(0, 3, AttributeType::FLOAT, GL_FALSE);
			vao.enableAttributes(attributes);
		}

		vao.unbind();
	}

public:
	void onRender() override
	{
		glm::mat4 model(1.0);

		model = glm::rotate(model, glm::radians(45.f), glm::vec3(0.f, 0.f, 1.f));

		auto shader = m_Shaders.get("main");
		shader.bind();
		shader.setMatrix4f("u_model", model);

		vao.bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

private:
	VertexArray vao;
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
