#pragma once
#include "pch.h"
#include "IRenderCommand.h"

namespace dat
{
	class Renderer
	{
	public:
		explicit Renderer() = default;
		~Renderer() = default;

	public:
		void initialize()
		{
			DAT_CORE_INFO("OpengGL Information:\n\t* Vendor: {}\n\t* Renderer: {}\n\t* Version: {}\n",
				(const char*)glGetString(GL_VENDOR),
				(const char*)glGetString(GL_RENDERER),
				(const char*)glGetString(GL_VERSION));

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);

			glDepthFunc(GL_LEQUAL);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		void shutdown()
		{
			m_Commands.clear();
		}

	public:
		void setColor(const glm::vec4& color)
		{
			glClearColor(color.r, color.g, color.b, color.a);
		}

		void setWireframe(bool enabled)
		{
			if(enabled)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		void clear()
		{
			m_Commands.clear();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

	public:
		void addCommand(std::unique_ptr<IRenderCommand> command)
		{
			m_Commands.push_back(std::move(command));
		}

		void executeCommands()
		{
			while (m_Commands.size() > 0)
			{
				auto renderCommand = std::move(m_Commands.front());

				renderCommand->Render();

				m_Commands.pop_front();
			}
		}

	private:
		std::deque<std::unique_ptr<IRenderCommand>> m_Commands;
	};
}