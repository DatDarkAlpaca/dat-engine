#pragma once
#include "Core/Assets/TextureAsset.hpp"

namespace dat
{
	class AssetLibrary
	{
	public:
		AssetHandle InsertTexture(const TextureAsset& textureAsset)
		{
			m_Textures.push_back(dat::MakeShared<TextureAsset>(textureAsset));
			return AssetHandle(m_Textures.size() - 1);
		}

		dat_weak<TextureAsset> GetTexture(AssetHandle handle)
		{
			return m_Textures[static_cast<size_t>(handle)];
		}

	private:
		std::vector<dat_shared<TextureAsset>> m_Textures;
	};
}