#pragma once
#include "pch.h"
#include "Mesh.h"
#include "Shader.h"
#include "IRenderCommand.h"

namespace dat
{
	class RenderMesh : public IRenderCommand
	{
	public:
		explicit RenderMesh(std::weak_ptr<Mesh> mesh, std::weak_ptr<Shader> shader)
			: m_Mesh(mesh), m_Shader(shader)
		{
		}

	public:
		void Render() override
		{
			auto mesh = m_Mesh.lock();
			auto shader = m_Shader.lock();

			if (mesh && shader)
			{
				mesh->bind();
				shader->use();

				if(mesh->getElementCount() > 0)
					glDrawElements(GL_TRIANGLES, mesh->getElementCount(), GL_UNSIGNED_INT, 0);
				else
					glDrawArrays(GL_TRIANGLE_STRIP, 0, mesh->getVertexCount());

				return;
			}

			DAT_CORE_ERROR("Attempted to render an invalid mesh and/or shader.");
		}

	private:
		std::weak_ptr<Mesh> m_Mesh;
		std::weak_ptr<Shader> m_Shader;
	};
}