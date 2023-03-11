#pragma once
#include "Graphics/Shader.h"

namespace dat
{
	template<typename Resource>
	class ResourceHolder
	{
	public:
		void add(std::string_view resourceName, std::shared_ptr<Resource>&& resource);

		Resource& get(std::string_view resourceName)
		{
			return *m_Resources[resourceName];
		}

	protected:
		std::unordered_map<std::string_view, std::shared_ptr<Resource>> m_Resources;
	};
}