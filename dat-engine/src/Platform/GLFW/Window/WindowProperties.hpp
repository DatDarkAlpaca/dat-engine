#pragma once
#include <string>
#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

#include "Common.hpp"

namespace dat::platform
{
	struct WindowProperties
	{
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(WindowProperties, windowTitle,
			dimensions, position, minSize, maxSize)

	public:
		enum Position : int { DEFAULT = -1 };

		std::string windowTitle = "DatWindow v1.0";
		glm::vec2 dimensions = glm::vec2(640, 480);
		glm::vec2 position = glm::vec2(Position::DEFAULT, Position::DEFAULT);
		glm::vec2 minSize = glm::vec2(0), maxSize = dimensions;
	};
}