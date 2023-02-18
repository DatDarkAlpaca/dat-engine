#include "pch.h"
#include "Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Todo: separate the file loading from the texture.
namespace dat::graphics
{
	Texture2D::Texture2D(const char* texturePath, const TextureProperties& properties)
		: m_Properties(properties)
	{
		glGenTextures(1, &m_ID);
		initialize(texturePath);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_ID);
	}

	void Texture2D::initialize(const char* texturePath)
	{
		stbi_set_flip_vertically_on_load(true);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	
		m_Properties.width = width;
		m_Properties.height = height;

		glBindTexture(GL_TEXTURE_2D, m_ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_Properties.wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_Properties.wrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_Properties.filterMin);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_Properties.filterMax);

		if (nrChannels == 4)
		{
			m_Properties.imageFormat = GL_RGBA;
			m_Properties.textureFormat = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, m_Properties.textureFormat, width, height, 0, m_Properties.imageFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
	}
}
