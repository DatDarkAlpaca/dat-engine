#pragma once
#include <filesystem>
#include "TextureAsset.hpp"

namespace dat
{
	class TextureLoader
	{
	public:
		static TextureAsset Load(const std::filesystem::path& filepath);
	};
}