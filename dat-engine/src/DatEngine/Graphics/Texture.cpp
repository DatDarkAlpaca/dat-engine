#include "pch.h"
#include "Texture.h"
#include "Core/Logger.h"

dat::graphics::Texture::Texture(const std::string& filepath)
	: m_Filepath(filepath)
{
	loadImage();

	glGenTextures(1, &m_ID);
	bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Buffer);

	unbind();

	cleanupImage();
}

dat::graphics::Texture::~Texture()
{
	glDeleteTextures(1, &m_ID);
}

void dat::graphics::Texture::loadImage()
{
	stbi_set_flip_vertically_on_load(true);
	m_Buffer = stbi_load(m_Filepath.c_str(), &m_Width, &m_Height, &m_Channels, STBI_rgb_alpha);

	if (!m_Buffer)
		DAT_CORE_ERROR("Could not load texture.");
}

void dat::graphics::Texture::cleanupImage()
{
	if (m_Buffer)
		stbi_image_free(m_Buffer);
}

void dat::graphics::Texture::bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}
