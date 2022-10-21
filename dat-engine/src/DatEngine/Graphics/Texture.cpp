#include "pch.h"
#include "Texture.h"

dat::Texture2D::Texture2D()
{
	glGenTextures(1, &ID);
}

void dat::Texture2D::generate(unsigned int width, unsigned int height, unsigned char* data)
{
	this->width = width;
	this->height = height;

	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void dat::Texture2D::bind() const
{
	glBindTexture(GL_TEXTURE_2D, ID);
}
