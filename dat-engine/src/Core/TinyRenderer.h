#pragma once
#include "API.h"
#include "Graphics/Shader.h"

namespace { using namespace dat; }

namespace dat
{
	class TinyRenderer
	{
	public:
		void draw(Shader& shader, unsigned int VAO, unsigned int VBO = -1, unsigned int count = 0)
		{
			glBindVertexArray(VAO);
			
			shader.bind();

			if (VBO != -1) 
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);
				glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
				return;
			}

			glDrawArrays(GL_TRIANGLES, 0, count);
		}
	};
}