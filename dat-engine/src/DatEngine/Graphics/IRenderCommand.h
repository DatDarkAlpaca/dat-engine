#pragma once

namespace dat
{
	class IRenderCommand
	{
	public:
		virtual ~IRenderCommand() = default;

	public:
		virtual void Render() = 0;
	};
}