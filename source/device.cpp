#include "device.hpp"
#include "vlayers.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>

vkoDevice::vkoDevice(VkInstance &instance, VkSurfaceKHR &surface) : _instance{ instance }
{
	BuildPhysicalDevice(surface);
	BuildLogicalDevice(surface);
}

vkoDevice::~vkoDevice()
{
}

void vkoDevice::BuildPhysicalDevice(VkSurfaceKHR& surface)
{
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
		if (VerifyDevice(device, surface)) 
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

void vkoDevice::BuildLogicalDevice(VkSurfaceKHR& surface)
{
	QueueFamilyIndices indices = FindQueueFamilies(physicalDevice, surface);

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

	float queuePriority = 1.0f;

	for (uint32_t queueFamily : uniqueQueueFamilies) {
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = queueCreateInfos.data(); 
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = deviceExtensions.data();

	if (vlayers::enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(vlayers::validationLayers.size());
		createInfo.ppEnabledLayerNames = vlayers::validationLayers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &_device) != VK_SUCCESS) {
		throw std::runtime_error("failed to create logical device!");
	}
	vkGetDeviceQueue(_device, indices.graphicsFamily.value(), 0, &graphicsQueue);
	vkGetDeviceQueue(_device, indices.presentFamily.value(), 0, &presentQueue);
}

void vkoDevice::DestroyLogicalDevice()
{
	vkDestroyDevice(_device, nullptr);
}

bool vkoDevice::VerifyDevice(VkPhysicalDevice device, VkSurfaceKHR& surface)
{
	QueueFamilyIndices indices = FindQueueFamilies(device, surface);

	bool extensionSupported = checkDeviceExtensionSupport(device);

	bool swapChainAdequate = false;

	if (extensionSupported)
	{
		supportDetails = querySwapChainSupport(device, surface);
		swapChainAdequate = !supportDetails.formats.empty() && !supportDetails.presentModes.empty();

	}

	return indices.isComplete() && extensionSupported && swapChainAdequate;
}

bool vkoDevice::checkDeviceExtensionSupport(VkPhysicalDevice device)
{
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

	for (const auto& extension : availableExtensions) {
		requiredExtensions.erase(extension.extensionName);
	}

	return requiredExtensions.empty();
}

QueueFamilyIndices vkoDevice::FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR& surface)
{
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

		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

		if (presentSupport) {
			indices.presentFamily = i;
		}

		if (indices.isComplete()) {
			break;
		}

		i++;
	}

	return indices;
}

SwapChainSupportDetails vkoDevice::querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR& surface)
{
	SwapChainSupportDetails details;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);// CAPABILITIES

	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

	if (formatCount != 0) {
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());// FORMATS
	}

	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

	if (presentModeCount != 0) {
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());// PRESENT MODES
	}

	return details;
}

const SwapChainSupportDetails& vkoDevice::getSupportDetails() const
{
	return supportDetails;
}

VkDevice& vkoDevice::getLogicalDevice()
{
	return _device;
}

const VkPhysicalDevice& vkoDevice::getPhysicalDevice() const
{
	return physicalDevice;
}
