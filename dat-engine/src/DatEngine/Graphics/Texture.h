#pragma once
#include "stb_image/stb_image.h"

namespace dat::graphics
{
	class Texture
	{
	public:
		Texture(const std::string& filepath);
		~Texture();

	private:
		void loadImage();

		void cleanupImage();

	public:
		void bind(unsigned int slot = 0) const;

		void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

	public:
		inline int getWidth() const { return m_Width; }

		inline int getHeight() const { return m_Height; }

	private:
		unsigned char* m_Buffer = nullptr;
		std::string m_Filepath;
		unsigned int m_ID;

	private:
		int m_Width = 0, m_Height = 0, m_Channels = 0;
	};
}