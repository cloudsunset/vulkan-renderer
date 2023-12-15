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
	size_t imageCount() { return swapChainImages.size(); }
	VkExtent2D getSwapChainExtent() { return swapChainExtent; }

	void DestroySwapChainKHR();
	void DestroySyncObjects();
	void DestroyFramebuffers();
	void DestroyImageViews();
	void DestroyRenderPass();


	VkResult acquireNextImage(uint32_t* imageIndex);
	VkResult submitCommandBuffers(const VkCommandBuffer* commandBuffers, uint32_t* imageIndex, VkQueue graphicsQueue, VkQueue presentQueue);

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

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;

	uint32_t currentFrame = 0;

	void createRenderPass();
	
	void createImageViews();

	void createFrameBuffers();

	void createSyncObjects();

	VkSurfaceFormatKHR setSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR setPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D setExtent(const VkSurfaceCapabilitiesKHR& capabilities, const std::shared_ptr<vkoWindow>& window);

};