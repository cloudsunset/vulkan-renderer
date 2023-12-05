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
	VkFormat& getSwapChainImageFormat();
	VkRenderPass getRenderPass() { return renderPass; }
	VkFramebuffer getFrameBuffer(int index) { return swapChainFramebuffers[index]; }
	VkExtent2D getSwapChainExtent() { return swapChainExtent; }

	void DestroySwapChain();

	VkResult acquireNextImage(uint32_t* imageIndex, const VkCommandBuffer commandBuffer);
	VkResult submitCommandBuffers(const VkCommandBuffer commandBuffer, uint32_t* imageIndex, VkQueue graphicsQueue, VkQueue presentQueue);

private:

	VkSwapchainKHR swapChain;
	SwapChainSupportDetails supportDetails;
	QueueFamilyIndices indices;
	VkDevice& device;

	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;

	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	VkRenderPass renderPass;

	std::vector<VkFramebuffer> swapChainFramebuffers;

	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
	VkFence inFlightFence;


	void createRenderPass();
	
	void createImageViews();

	void createFrameBuffers();

	void createSyncObjects();

	VkSurfaceFormatKHR setSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR setPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D setExtent(const VkSurfaceCapabilitiesKHR& capabilities, const std::shared_ptr<vkoWindow>& window);



};