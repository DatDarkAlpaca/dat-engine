#pragma once
#include "pch.h"

namespace dat
{
	class Texture2D
	{
	public:
		Texture2D();

	public:
		void generate(unsigned int width, unsigned int height, unsigned char* data);

		void bind() const;

	public:
		unsigned int ID = 0;
		unsigned int width = 0, height = 0;

		unsigned int internalFormat = GL_RGB, imageFormat = GL_RGB;
		unsigned int wrapS = GL_REPEAT, wrapT = GL_REPEAT, filterMin = GL_NEAREST, filterMax = GL_NEAREST;
	};
}