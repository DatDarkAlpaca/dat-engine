#pragma once

namespace dat
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
}