#pragma once
#include <string>

namespace dat::utils 
{
	inline std::string readFile(const std::string& filepath)
	{
		std::ifstream file(filepath);

		std::ostringstream oss;
		oss << file.rdbuf();

		std::string result = oss.str();

		return result;
	}
}