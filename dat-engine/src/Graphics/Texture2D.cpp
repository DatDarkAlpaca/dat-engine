#include "pch.h"
#include "Utils/Logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Texture2D.h"

namespace
{
	void createTexture(const char* texturePath, dat::TextureProperties& properties)
	{
		stbi_set_flip_vertically_on_load(true);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

		if (!data)
		{
			DAT_CORE_ERROR("Failed to load texture: {}", texturePath);
			return;
		}

		properties.width = width;
		properties.height = height;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, properties.wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, properties.wrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, properties.filterMin);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, properties.filterMax);

		if (nrChannels == 4)
		{
			properties.imageFormat = GL_RGBA;
			properties.textureFormat = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, properties.textureFormat, width, height, 0, properties.imageFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}
}

namespace dat
{
	Texture2D::Texture2D(const char* texturePath, const TextureProperties& properties)
		: m_Properties(properties)
	{
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);

		createTexture(texturePath, m_Properties);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_ID);
	}

	void Texture2D::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	void Texture2D::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
