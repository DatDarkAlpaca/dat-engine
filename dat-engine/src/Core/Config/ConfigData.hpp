#pragma once
#include "Core/Engine/AppSpecification.hpp"
#include "Graphics/GraphicsSpecification.hpp"

#include "Platform/Platform.hpp"

namespace dat
{
	struct ConfigData
	{
		AppSpecification appSpecification;
		platform::WindowProperties windowProperties;
		graphics::GraphicsSpecification graphicsSpecification;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(ConfigData, appSpecification, windowProperties, graphicsSpecification);
	};
}