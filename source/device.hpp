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

	VkDevice& getLogicalDevice();

	const VkPhysicalDevice& getPhysicalDevice() const;

	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR& surface);

	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR& surface);

	VkCommandPool& getCommandPool();

	VkQueue getGraphicsQueue();
	VkQueue getPresentQueue();

	void DestroyLogicalDevice();
	void DestroyCommandPool();

private:

	VkInstance &_instance;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice _device;

	QueueFamilyIndices indices;

	VkQueue graphicsQueue;
	VkQueue presentQueue;

	SwapChainSupportDetails supportDetails;

	VkCommandPool commandPool;
	
	void BuildPhysicalDevice(VkSurfaceKHR& surface);

	void BuildLogicalDevice(VkSurfaceKHR& surface);

	void CreateCommandPool();

	bool VerifyDevice(VkPhysicalDevice device, VkSurfaceKHR& surface);

	bool checkDeviceExtensionSupport(VkPhysicalDevice device);

};