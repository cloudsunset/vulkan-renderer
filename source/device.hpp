#pragma once
#include "window.hpp"
#include <optional>

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

class vkoDevice
{
public:

	vkoDevice(VkInstance &instance, VkSurfaceKHR& surface);
	~vkoDevice();

	VkPhysicalDeviceProperties properties{};
	VkPhysicalDeviceFeatures deviceFeatures{};

private:

	VkInstance &_instance;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice _device;

	VkQueue graphicsQueue;
	VkQueue presentQueue;
	

	void BuildPhysicalDevice(VkSurfaceKHR& surface);

	void BuildLogicalDevice(VkSurfaceKHR& surface);


	void DestroyLogicalDevice();

	bool VerifyDevice(VkPhysicalDevice device, VkSurfaceKHR& surface);

	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR& surface);

};