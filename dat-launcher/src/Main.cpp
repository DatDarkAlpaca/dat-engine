#include <DatEngine.h>

using namespace dat;

// Game specific:
struct Transform
{
	glm::vec2 position;
	glm::vec2 size;
	float rotation = 0.f;
};

static Transform cactusTransform = {
	{ 800.f + 125 / 2.f, 600.f - 125.f / 2.f },
	{ 125.f, 125.f }
};
static constexpr float cactusSpeed = 450.f;

static Transform dinoTransform = {
	{ 75.f, 600.f - 125.f / 2.f },
	{ 125.f, -125.f }
};
static float dinoVelocityY = 0.f;
static float dinoAccelerationY = 0.f;
static bool gameOver = false;

// Physics:
bool isGrounded(Transform& object)
{
	return object.position.y >= 600 - object.size.x / 2;
}

void clampGround(Transform& object)
{
	if (object.position.y >= 600.f - object.size.x / 2.f)
		object.position.y = 600.f - object.size.x / 2.f;
}

void clampCactus(Transform& object)
{
	if (object.position.x <= 0)
		object.position.x = 800;
}

bool AABB(const Transform& a, const Transform& b)
{
	return (
		a.position.x + a.size.x > b.position.x + 45.f &&
		a.position.y - a.size.y > b.position.y
	);
}

// Layers:
struct PlayerInput
{
	void onEvent(IEvent& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<KeyPressedEvent>([&](KeyPressedEvent& keyEvent) {
			if (keyEvent.key == GLFW_KEY_SPACE)
				spacePressed = true;
			return true;
		});

		dispatcher.dispatch<KeyRepeatEvent>([&](KeyRepeatEvent& keyEvent) {
			if (keyEvent.key == GLFW_KEY_SPACE)
				spacePressed = true;
			return true;
		});

		dispatcher.dispatch<KeyReleasedEvent>([&](KeyReleasedEvent& keyEvent) {
			if (keyEvent.key == GLFW_KEY_SPACE)
				spacePressed = false;
			return true;
		});
	}

	bool spacePressed = false;
};

class DinoRipoff : public ILayer
{
public:
	DinoRipoff(DatApplication* app) : ILayer(app)
	{
		glClearColor(135.f / 255.f, 206 / 255.f, 250 / 255.f, 1.0);
		glEnable(GL_BLEND);
		
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_Camera = new OrthoCamera(0.f, 800.f, 600.f, 0.f, -10.f, 100.f);

		m_CactusTexture = std::make_shared<Texture2D>("res/cactus.png");
		m_DinoTexture = std::make_shared<Texture2D>("res/dino.png");

		dinoTransform.position.y = 100.f;
	}

	void onUpdate(Timestep dt) override
	{
		if (gameOver)
		{
			if (Input::isKeyDown(KEY_ENTER))
			{
				gameOver = false;

				dinoTransform = {
					{ 75.f, 600.f - 125.f / 2.f },
					{ 125.f, -125.f }
				};

				cactusTransform = {
					{ 800.f + 125 / 2.f, 600.f - 125.f / 2.f },
					{ 125.f, 125.f }
				};
			}

			return;
		}
		
		// Misc:
 		m_Camera->onUpdate(dt);
		cactusTransform.position.x -= dt.timestep() * cactusSpeed;
		
		// Add Force:
		dinoAccelerationY += 980.f;

		if(isGrounded(dinoTransform))
			dinoVelocityY = 0.f;

		if (isGrounded(dinoTransform) && m_Input.spacePressed)
			dinoVelocityY -= 750.f;

		// Collision:
		if (AABB(dinoTransform, cactusTransform))
		{
			gameOver = true;
			return;
		}

		// Update:
		dinoVelocityY += dinoAccelerationY * dt.timestep();
		dinoTransform.position.y += dinoVelocityY * dt.timestep();

		dinoAccelerationY = 0.f;

		// Clamp:
		clampGround(dinoTransform);
		clampCactus(cactusTransform);
	}

	void onRender() override
	{
		Renderer2D::beginScene(*m_Camera);

		Renderer2D::submitQuad(cactusTransform.position, cactusTransform.size, glm::vec4(1.f), 180.f, m_CactusTexture);
		
		if(gameOver)
			Renderer2D::submitQuad(dinoTransform.position, dinoTransform.size, glm::vec4(0.97f, 0.1f, 0.1f, 1.0f), 0.f, m_DinoTexture);
		else
			Renderer2D::submitQuad(dinoTransform.position, dinoTransform.size, glm::vec4(1.f), 0.f, m_DinoTexture);
	}

	void onEvent(IEvent& event) override
	{
		m_Input.onEvent(event);
	}

private:
	dat_shared<Texture2D> m_CactusTexture;
	dat_shared<Texture2D> m_DinoTexture;
	OrthoCamera* m_Camera;

private:
	PlayerInput m_Input;
};

class Client : public DatApplication
{
public:
	Client(int width, int height, const char* title)
		: DatApplication(width, height, title)
	{
		layers().addLayer(new DinoRipoff(this));
	}
};

int main()
{
	auto c = Client(800, 600, "Dat Engine");
	c.run();
}
