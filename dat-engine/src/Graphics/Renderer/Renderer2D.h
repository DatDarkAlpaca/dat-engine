#pragma once
#include "pch.h"

#include "Graphics/OpenGL/Shader.h"
#include "Graphics/OpenGL/Texture2D.h"
#include "Graphics/Camera/ICamera.h"

namespace dat
{
	class DAT_API Renderer2D
	{
	public:
		static void initialize();

	public:
		static void beginScene(const ICamera& camera);

	public:
		static void submitQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float rotation);

		static void submitQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float rotation);

		static void submitQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, float rotation, dat_shared<Texture2D> texture);

		static void submitQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, float rotation, dat_shared<Texture2D> texture);
	};
}