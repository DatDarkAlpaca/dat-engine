#include <DatEngine.h>

struct Transform
{
	glm::vec3 position{ 0.f };
	glm::vec3 eulerRotation{ 0.f };
	glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

	glm::mat4 modelMatrix = glm::mat4(1.0f);
};

void main()
{
	auto app = dat::core::DatApplication(800, 600, "Title");
	app.run();
}