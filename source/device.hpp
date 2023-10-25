#pragma once
#include "window.hpp"
#include <optional>
#include <vector>

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

const std::vector<const char*> deviceExtensions =
{
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

class vkoDevice
{
public:

	vkoDevice(VkInstance &instance, VkSurfaceKHR& surface);
	~vkoDevice();

	VkPhysicalDeviceProperties properties{};
	VkPhysicalDeviceFeatures deviceFeatures{};

	const SwapChainSupportDetails& getSupportDetails() const;

	const VkDevice& getLogicalDevice() const;

	const VkPhysicalDevice& getPhysicalDevice() const;

	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR& surface);

	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR& surface);

private:

	VkInstance &_instance;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice _device;

	VkQueue graphicsQueue;
	VkQueue presentQueue;

	SwapChainSupportDetails supportDetails;
	
	void BuildPhysicalDevice(VkSurfaceKHR& surface);

	void BuildLogicalDevice(VkSurfaceKHR& surface);

	void DestroyLogicalDevice();

	bool VerifyDevice(VkPhysicalDevice device, VkSurfaceKHR& surface);

	bool checkDeviceExtensionSupport(VkPhysicalDevice device);

	




};