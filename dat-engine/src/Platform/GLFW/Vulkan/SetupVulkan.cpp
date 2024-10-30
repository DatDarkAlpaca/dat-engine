#include "pch.hpp"
#include "SetupVulkan.hpp"

#include <GLFW/glfw3.h>

namespace dat::platform::vulkan
{
	void SetupVulkanWindowing(Window& window, const WindowProperties& properties)
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		if (!glfwVulkanSupported())
			DAT_LOG_CRITICAL("Vulkan is not supported in this machine");

		window.Initialize(properties);
	}

	std::vector<const char*> GetWindowingVulkanExtensions()
	{
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
		return extensions;
	}

	VkSurfaceKHR GetVulkanSurface(vk::Instance instance, Window* window)
	{
		VkSurfaceKHR surface;
		VkResult result = glfwCreateWindowSurface(instance, std::any_cast<GLFWwindow*>(window->GetHandle()), nullptr, &surface);

		if (result == VK_SUCCESS)
			return surface;

		DAT_LOG_CRITICAL("Failed to create window surface using GLFW and Vulkan");
		return nullptr;
	}

	std::vector<const char*> GetVulkanExtensionPlatformSurfaceNames()
	{
#ifdef DAT_PLATFORM_WINDOWS
		return { "VK_KHR_win32_surface" };

#elif defined(DAT_PLATFORM_LINUX)
		return {
			"VK_KHR_xcb_surface",
			"VK_KHR_xlib_surface",
			"VK_KHR_wayland_surface"
		};
#elif defined(DAT_PLATFORM_MACOSX)
		return { "VK_EXT_metal_surface" };

#elif defined(DAT_PLATFORM_ANDROID)
		return { "VK_KHR_android_surface" };
#endif
	}
}