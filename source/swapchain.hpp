#pragma once
#include "window.hpp"
#include "device.hpp"
#include <vector>
#include <vulkan/vulkan.h>

class vkoSwapChain
{
public:
	vkoSwapChain(std::shared_ptr<vkoDevice>& device, const std::shared_ptr<vkoWindow>& window);
	~vkoSwapChain();

	void configSwapChain(VkSurfaceFormatKHR& surfaceFormat, VkPresentModeKHR& presentMode,VkExtent2D& extent, const std::shared_ptr<vkoWindow>& window, const SwapChainSupportDetails& supportedProperties);

	void DestroySwapChain();

private:

	VkSwapchainKHR swapChain;
	SwapChainSupportDetails supportDetails;
	VkDevice& device;

	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;

	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	
	void createImageViews();

	VkSurfaceFormatKHR setSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR setPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D setExtent(const VkSurfaceCapabilitiesKHR& capabilities, const std::shared_ptr<vkoWindow>& window);



};