#pragma once
#include <numeric>
#include <nlohmann/json.hpp>

#include "GraphicsAPI.hpp"

namespace dat::graphics
{
	struct GraphicsSpecification
	{
		GraphicsAPI api = GraphicsAPI::UNKNOWN;
		uint8_t major = 0, minor = 0, patch = 0, variant = 0;
	};

	inline void to_json(nlohmann::json& json, const GraphicsSpecification& specification)
	{
		json["api"] = GetGraphicsAPIString(specification.api);
		json["major"] = specification.major;
		json["minor"] = specification.minor;
		json["patch"] = specification.patch;
		json["variant"] = specification.variant;
	}

	inline void from_json(const nlohmann::json& json, GraphicsSpecification& specification)
	{
		specification.api = GetGraphicsAPIFromString(json.at("api"));
		specification.major = json.at("major");
		specification.minor = json.at("minor");
		specification.patch = json.at("patch");
		specification.variant = json.at("variant");
	}
}