#pragma once
#include <fstream>
#include <nlohmann/json.hpp>
#include "Core/Logger/Logger.hpp"

namespace dat
{
	inline nlohmann::json ReadJson(const std::filesystem::path& filepath)
	{
		using namespace nlohmann;

		std::ifstream file(filepath);
		return json::parse(file);
	}
}