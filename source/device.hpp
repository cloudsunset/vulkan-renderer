#pragma once
#include "window.hpp"


struct QueueFamilyIndices
{
	uint32_t graphicsFamily;
	uint32_t presentFamily;
	bool graphicsFamilyHasValue = false;
	bool presentFamilyHasValue = false;
	bool isComplete() { return graphicsFamilyHasValue && presentFamilyHasValue; }
};

class vkoDevice
{
public:

	vkoDevice(VkInstance &instance, vkoWindow &window);
	~vkoDevice();

	VkPhysicalDeviceProperties properties;

private:

	VkInstance &_instance;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice _device;
	vkoWindow &_window;

	void BuildPhysicalDevice();

	bool VerifyDevice(VkPhysicalDevice device);

	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

};