#include <DatEngine.h>

using namespace dat;

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

struct PlayerSprite
{
	glm::vec2 position{ 100.f, 400.f };
	glm::vec2 size{ 50.f, 50.f };
	float rotationAngle = 0;
	glm::vec3 color{ 1.f, 1.f, 1.f };
	Texture2D* texture = nullptr;
};

void updateGravity(PlayerSprite& sprite)
{
	sprite.position.y += 0.10f;
}

void clampGround(PlayerSprite& sprite)
{
	if (sprite.position.y >= 600 - sprite.size.x / 2)
		sprite.position.y = 600 - sprite.size.x / 2;
}

bool isGrounded(PlayerSprite& sprite)
{
	return sprite.position.y >= 600 - sprite.size.x / 2;
}

void moveCactus(PlayerSprite& sprite)
{
	sprite.position.x -= 0.1f;
}

void clampCactus(PlayerSprite& cactus)
{
	if(cactus.position.x <= 0)
		cactus.position.x = 800;
}

bool AABB(PlayerSprite& a, PlayerSprite& b)
{
	auto aPos = a.position;
	auto bPos = b.position;
	auto aSize = a.size;
	auto bSize = b.size;

	return aPos.x < bPos.x + bSize.x && aPos.x + aSize.x > bPos.x &&
		aPos.y < bPos.y + bSize.y && aSize.y + aPos.y > bPos.y;
}

class GameLayer : public dat::ILayer
{
public:
	void onLayerAdded() override
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_Shaders.add("quad", std::make_shared<Shader>("res/sprite_vert.glsl", "res/sprite_frag.glsl"));
		Shader* shader = m_Shaders.get("quad");
		m_Renderer.setShader(shader);
		m_Renderer.initialize();
		shader->bind().setInteger("u_texture", 0);

		glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
		shader->bind().setMatrix4f("u_projection", projection);

		m_Textures.add("player", std::make_shared<Texture2D>("res/player.png"));
		m_PlayerSprite.texture = m_Textures.get("player");

		m_Textures.add("cactus", std::make_shared<Texture2D>("res/cactus.png"));
		m_Cactus.texture = m_Textures.get("cactus");

		m_Textures.add("gameover", std::make_shared<Texture2D>("res/game_over.png"));
		m_GameOver.texture = m_Textures.get("gameover");
		m_GameOver.size = {135 * 2, 40 * 2};
		m_GameOver.position = { 200, 200 };
		m_Cactus.position = { 500, 600 - m_Cactus.size.x / 2 };
	}

	void onUpdate() override
	{
		if (AABB(m_PlayerSprite, m_Cactus))
		{
			renderGameOver = true;
			if (m_Input.spacePressed)
			{
				m_PlayerSprite.position = { 100.f, 400.f };
				m_Cactus.position = { 500, 600 - m_Cactus.size.x / 2 };
				renderGameOver = false;
				return;
			}
			return;
		}

		updateGravity(m_PlayerSprite);
		clampGround(m_PlayerSprite);

		moveCactus(m_Cactus);
		clampCactus(m_Cactus);

		if (isGrounded(m_PlayerSprite) && m_Input.spacePressed)
		{
			m_PlayerSprite.position.y = 300.f;
		}
	}

	void onRender() override
	{ 
		glClearColor(1, 1, 1, 1);

		if(renderGameOver)
			m_Renderer.drawQuad(*m_GameOver.texture,
				m_GameOver.position,
				m_GameOver.size,
				m_GameOver.rotationAngle,
				m_GameOver.color
			);

		m_Renderer.drawQuad(*m_Cactus.texture,
			m_Cactus.position,
			m_Cactus.size,
			m_Cactus.rotationAngle,
			m_Cactus.color
		);

		m_Renderer.drawQuad(*m_PlayerSprite.texture,
			m_PlayerSprite.position, 
			m_PlayerSprite.size, 
			m_PlayerSprite.rotationAngle, 
			m_PlayerSprite.color
		);
	}

	void onEvent(IEvent& event) override
	{ 
		m_Input.onEvent(event);
	}

private:
	ResourceHolder<Texture2D> m_Textures;
	ResourceHolder<Shader> m_Shaders;

	PlayerSprite m_PlayerSprite, m_Cactus, m_GameOver;
	QuadRenderer m_Renderer;
	PlayerInput m_Input;

	bool renderGameOver = false;
};

int main()
{
	auto game = DatApplication(800, 600, "Dat Engine");
	game.layers().addLayer(new GameLayer());

	game.run();
}
