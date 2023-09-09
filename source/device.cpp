#include "device.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

vkoDevice::vkoDevice(VkInstance &instance, vkoWindow &window) : _instance{ instance }, _window{ window }
{
	BuildPhysicalDevice();
}

vkoDevice::~vkoDevice()
{

}

void vkoDevice::BuildPhysicalDevice()
{
	
}

bool vkoDevice::VerifyDevice(VkPhysicalDevice device)
{
	QueueFamilyIndices indices = FindQueueFamilies(device);

	return indices.isComplete();
}

QueueFamilyIndices vkoDevice::FindQueueFamilies(VkPhysicalDevice device)
{
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	for (auto& q_family : queueFamilies)
	{
		std::cout << "Queue number: " + std::to_string(q_family.queueCount) << std::endl;
		std::cout << "Queue flags: " + std::to_string(q_family.queueFlags) << std::endl;
	}

	int i = 0;

	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
			indices.graphicsFamilyHasValue = true;
		}
		VkBool32 presentSupport = false;
		//vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface_, &presentSupport);
		if (queueFamily.queueCount > 0 && presentSupport) {
			indices.presentFamily = i;
			indices.presentFamilyHasValue = true;
		}
		if (indices.isComplete()) {
			break;
		}

		i++;
	}

	return indices;
}
