#pragma once
#include "Core/Config/ConfigData.hpp"
#include "Platform/Platform.hpp"

namespace dat::graphics
{
	inline void InitializeGraphics(const ConfigData& configData, platform::Window& window)
	{
		const auto& graphicsProps = configData.graphicsSpecification;
		const auto& windowProps = configData.windowProperties;

		switch (graphicsProps.api)
		{
			case graphics::GraphicsAPI::OPENGL:
			{
				platform::gl::SetupOpenGLWindowing(window, windowProps, graphicsProps);
			} break;

			case graphics::GraphicsAPI::VULKAN:
			{
				platform::vulkan::SetupVulkanWindowing(window, windowProps);
				// TODO: Vulkan initializer.
			} break;
		}
	}
}