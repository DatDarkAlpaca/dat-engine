#pragma once
#include "TextureProperties.h"

namespace dat
{
	class Texture2D
	{
	public:
		Texture2D(const char* texturePath, const TextureProperties& properties = {});
		~Texture2D();

	public:
		void bind() const;

		void unbind() const;

	private:
		TextureProperties m_Properties;
		unsigned int m_ID = 0;
	};
}