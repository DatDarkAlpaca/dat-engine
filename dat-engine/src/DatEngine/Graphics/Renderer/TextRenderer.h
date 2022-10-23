#pragma once
#include "pch.h"

#include "DatEngine/Graphics/Shader.h"
#include "DatEngine/Core/ResourceManager.h"

// Prodly stolen and slightly modified from:
// https://learnopengl.com/In-Practice/2D-Game/Render-text

namespace dat
{
	struct Character
	{
		unsigned int textureID, advance;
		glm::ivec2 size, bearing;
	};

	class TextRenderer
	{
	public:
		TextRenderer(size_t width, size_t height, std::string_view fontName, size_t fontSize)
		{
			initializeShader(width, height);

			initializeFont(fontName, fontSize);
		}

	private:
		void initializeShader(size_t width, size_t height)
		{
			m_TextShader = ResourceManager::getShader("text_shader");

			m_TextShader.use();
			m_TextShader.setMatrix4f("projection", glm::ortho(0.0f, float(width), float(height), 0.0f));
			m_TextShader.setInteger("text", 0);

			glGenVertexArrays(1, &m_VAO);

			glGenBuffers(1, &m_VBO);
			glBindVertexArray(m_VAO);

			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		void initializeFont(std::string_view fontName, size_t fontSize)
		{
			m_Characters.clear();

			FT_Library ft;
			if (FT_Init_FreeType(&ft))
			{
				DAT_CORE_ERROR("Failed to initialize the FreeType library.");
				return;
			}

			FT_Face face;
			if (FT_New_Face(ft, fontName.data(), 0, &face))
			{
				DAT_CORE_ERROR("Failed to load font: {}", fontName.data());
				return;
			}

			FT_Set_Pixel_Sizes(face, 0, (FT_UInt)fontSize);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			for (GLubyte character_code = 0; character_code < 128; character_code++)
			{
				if (FT_Load_Char(face, character_code, FT_LOAD_RENDER))
				{
					DAT_CORE_ERROR("Failed to load glyph: {}", character_code);
					continue;
				}

				unsigned int texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					face->glyph->bitmap.width,
					face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					face->glyph->bitmap.buffer
				);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				Character character = {
					texture,
					(size_t)face->glyph->advance.x,
					glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
					glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top)
				};

				m_Characters[character_code] = character;
			}

			glBindTexture(GL_TEXTURE_2D, 0);

			FT_Done_Face(face);
			FT_Done_FreeType(ft);
		}

	public:
		void render(std::string_view text, glm::vec2 position, float scale, glm::vec3 color = glm::vec3(1.0f))
		{
			m_TextShader.use();
			m_TextShader.setVector3f("textColor", color);
			glActiveTexture(GL_TEXTURE0);
			glBindVertexArray(m_VAO);

			for (auto it = text.begin(); it != text.end(); ++it)
			{
				Character ch = m_Characters[*it];

				float xpos = position.x + ch.bearing.x * scale;
				float ypos = position.y + (m_Characters['H'].bearing.y - ch.bearing.y) * scale;

				float w = ch.size.x * scale;
				float h = ch.size.y * scale;

				float vertices[6][4] = {
					{ xpos,     ypos + h,   0.0f, 1.0f },
					{ xpos + w, ypos,       1.0f, 0.0f },
					{ xpos,     ypos,       0.0f, 0.0f },

					{ xpos,     ypos + h,   0.0f, 1.0f },
					{ xpos + w, ypos + h,   1.0f, 1.0f },
					{ xpos + w, ypos,       1.0f, 0.0f }
				};

				glBindTexture(GL_TEXTURE_2D, ch.textureID);

				glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				glDrawArrays(GL_TRIANGLES, 0, 6);

				position.x += (ch.advance >> 6) * scale;
			}

			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	
	private:
		std::unordered_map<char, Character> m_Characters;

	private:
		Shader m_TextShader;
		unsigned int m_VAO = -1, m_VBO = -1;
	};
}