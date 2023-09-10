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
	//uint32_t deviceCount = 0;
	//
	//if (vkEnumeratePhysicalDevices(_instance, &deviceCount, nullptr) != VK_SUCCESS)
	//{
	//	throw std::runtime_error("vkEnumeratePhysicalDevices failed");
	//}
	//
	//if (deviceCount == 0) {
	//	throw std::runtime_error("No GPUs with Vulkan support!");
	//}
	//std::cout << "Device count: " << deviceCount << std::endl;
	//std::vector<VkPhysicalDevice> devices(deviceCount);
	//vkEnumeratePhysicalDevices(_instance, &deviceCount, devices.data());
	//
	//for (const auto& device : devices) {
	//	if (VerifyDevice(device)) {
	//		physicalDevice = device;
	//		break;
	//	}
	//}

	//if (physicalDevice == VK_NULL_HANDLE) {
	//	throw std::runtime_error("failed to find a suitable GPU!");
	//}
	//

	//try {
	//	vkGetPhysicalDeviceProperties(physicalDevice, &properties);
	//}
	//catch (const std::runtime_error& e) {
	//	std::cerr << "Runtime error: " << e.what() << std::endl;
	//	// Handle the error gracefully (e.g., clean up and exit)
	//}

	//

	//std::cout << "physical device: " << properties.deviceName << std::endl;

	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(_instance, &deviceCount, nullptr);

	if (deviceCount == 0) {
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(_instance, &deviceCount, devices.data());

	std::cout << "physical device: " << deviceCount << std::endl;

	for (const auto &device : devices) 
	{
		if (VerifyDevice(device)) 
		{

			physicalDevice = device;
			break;
		}
	}

	if (physicalDevice == VK_NULL_HANDLE) {
		throw std::runtime_error("failed to find a suitable GPU!");
	}

	vkGetPhysicalDeviceProperties(physicalDevice, &properties);
	std::cout << "physical device: " << properties.deviceName << std::endl;
	
}

bool vkoDevice::VerifyDevice(VkPhysicalDevice device)
{
	QueueFamilyIndices indices = FindQueueFamilies(device);

	return indices.isComplete();
	//return true;
}

QueueFamilyIndices vkoDevice::FindQueueFamilies(VkPhysicalDevice device)
{
	//QueueFamilyIndices indices;

	//uint32_t queueFamilyCount = 0;
	//vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	//std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	//vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	//for (auto& q_family : queueFamilies)
	//{
	//	std::cout << "Queue number: " + std::to_string(q_family.queueCount) << std::endl;
	//	std::cout << "Queue flags: " + std::to_string(q_family.queueFlags) << std::endl;
	//}

	//int i = 0;

	//for (const auto& queueFamily : queueFamilies) {
	//	if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
	//		indices.graphicsFamily = i;
	//		indices.graphicsFamilyHasValue = true;
	//	}
	//	VkBool32 presentSupport = false;
	//	//vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface_, &presentSupport);
	//	if (queueFamily.queueCount > 0 && presentSupport) {
	//		indices.presentFamily = i;
	//		indices.presentFamilyHasValue = true;
	//	}
	//	if (indices.isComplete()) {
	//		break;
	//	}

	//	i++;
	//}

	//return indices;

	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
		}

		if (indices.isComplete()) {
			break;
		}

		i++;
	}

	return indices;
}
