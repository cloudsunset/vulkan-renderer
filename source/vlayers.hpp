#pragma once
#include <vector>
#include <vulkan/vulkan.h>

namespace vlayers
{
	#ifdef NDEBUG
		const bool enableValidationLayers = false;
	#else 
		const bool enableValidationLayers = true;
	#endif

	const std::vector<const char*> validationLayers =
	{
		"VK_LAYER_KHRONOS_validation"
	};

	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	bool checkValidationLayerSupport();

	void BuildDebugMessenger(VkInstance& instance, VkDebugUtilsMessengerEXT& debugMessenger);

	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

}