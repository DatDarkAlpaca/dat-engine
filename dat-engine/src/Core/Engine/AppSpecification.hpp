#pragma once
#include <numeric>
#include <string>

namespace dat
{
	struct AppSpecification
	{
		std::string applicationName = "Default Application";
		uint32_t versionMajor = 1, versionMinor = 0, versionPatch = 0, versionVariant = 0;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(AppSpecification, versionMajor, versionMinor, versionPatch, versionVariant);
	};
}