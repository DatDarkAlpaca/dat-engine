#pragma once

namespace dat
{
	class Buffer
	{
	public:
		Buffer() = default;

	public:
		void* data = nullptr;
		size_t size = 0;
	};
}