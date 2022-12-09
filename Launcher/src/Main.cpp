#include <DatEngine/DatEngine.h>

using namespace dat;
using namespace core;
using namespace graphics;

int main()
{
	Window window(960, 540, "DatWindow!");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Texture:
	Texture texture("res/textures/image.png");

	// Shader MVP Setup:
	Shader shader("res/shaders/vertex.glsl", "res/shaders/fragment.glsl");
	shader.bind();

	glm::mat4 projection = glm::ortho(0.0f, 16.f, 0.0f, 9.f, -1.0f, 1.0f);
	shader.setMatrix4f("u_proj_matrix", projection);

	// Renderer:
	ImmediateRenderer2D renderer;

	BasicRenderCommand command(shader, texture, glm::vec3(0.f, 0.f, 0.f), 0, glm::vec3(3.f, 3.f, 0), glm::vec4(0.3f, 0.5f, 0.4f, 1.f));
	
	utils::Timer timer;
	renderer.clearColor(0.4f, 0.4f, 0.54f);
	while (!window.isClosed())
	{
		renderer.clear();

		renderer.push(&command);

		renderer.flush();

		window.update();
	}
}