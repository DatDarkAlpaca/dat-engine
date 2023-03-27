#pragma once
#include "Graphics/Shader.h"

namespace dat
{
	template<typename Resource>
	class ResourceHolder
	{
	public:
		dat_shared<Resource> add(std::string_view resourceName, dat_shared<Resource>&& resource)
		{
			m_Resources[resourceName] = std::move(resource);
			return m_Resources[resourceName];
		}

		dat_shared<Resource> get(std::string_view resourceName)
		{
			return m_Resources[resourceName];
		}

		void erase(std::string_view resourceName)
		{
			for (auto it = m_Resources.begin(); it != m_Resources.end();)
			{
				if (it->first == resourceName)
					it = m_Resources.erase(it);
				else
					it++;
			}
		}

	protected:
		std::unordered_map<std::string_view, dat_shared<Resource>> m_Resources;
	};
}