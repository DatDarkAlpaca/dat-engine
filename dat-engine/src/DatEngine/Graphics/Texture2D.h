#pragma once

namespace dat::graphics
{
	struct TextureProperties
	{
		unsigned int width = 0;
		unsigned int height = 0;

		unsigned int textureFormat = GL_RGB;
		unsigned int imageFormat = GL_RGB;

		unsigned int wrapS = GL_REPEAT;
		unsigned int wrapT = GL_REPEAT;

		unsigned int filterMin = GL_NEAREST;
		unsigned int filterMax = GL_NEAREST;
	};

	class Texture2D
	{
	public:
		Texture2D(const char* texturePath, const TextureProperties& properties = {});
		~Texture2D();

	private:
		void initialize(const char* texturePath);

	public:
		inline void bind() const { glBindTexture(GL_TEXTURE_2D, m_ID); }

	private:
		TextureProperties m_Properties;
		unsigned int m_ID = 0;
	};
}