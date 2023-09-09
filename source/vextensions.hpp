#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "vlayers.hpp"
#include <iostream>
#include <vector>


namespace vext
{

	std::vector<const char*> getRequiredExtensions()
	{
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (vlayers::enableValidationLayers) {
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		}

		return extensions;
	}

	void enumerateExtensions()
	{
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> extensionsp(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionsp.data());

		std::cout << "available extensions:\n";

		for (const auto& extension : extensionsp) {
			std::cout << '\t' << extension.extensionName << '\n';
		}
	}

}