#include "swapchain.hpp"
#include <cstdint> 
#include <limits> 
#include <algorithm>
#include <iostream>

vkoSwapChain::vkoSwapChain(std::shared_ptr<vkoDevice> device, const std::shared_ptr<vkoWindow>& window) : device{ device->getLogicalDevice()}
{
    VkSurfaceFormatKHR surfaceFormat;
    VkPresentModeKHR presentMode;
    VkExtent2D extent;

    SwapChainSupportDetails swapChainSupport = device->getSupportDetails();

    configSwapChain(surfaceFormat, presentMode, extent, window, swapChainSupport);

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

    
    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = window->getSurface();

    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;//This is always 1 unless you are developing a stereoscopic 3D application
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices indices = device->FindQueueFamilies(device->getPhysicalDevice(), window->getSurface());

    uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

    if (indices.graphicsFamily != indices.presentFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
        std::cout << "imageSharingMode = VK_SHARING_MODE_CONCURRENT" << std::endl;
    }
    else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0; // Optional
        createInfo.pQueueFamilyIndices = nullptr; // Optional
        std::cout << "imageSharingMode = VK_SHARING_MODE_EXCLUSIVE" << std::endl;
    }
    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    VkResult r = vkCreateSwapchainKHR(device->getLogicalDevice(), &createInfo, nullptr, &swapChain);

    if (r != VK_SUCCESS) {
        throw std::runtime_error("failed to create swap chain!");
    }

    vkGetSwapchainImagesKHR(device->getLogicalDevice(), swapChain, &imageCount, nullptr);
    swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(device->getLogicalDevice(), swapChain, &imageCount, swapChainImages.data());
}

vkoSwapChain::~vkoSwapChain()
{
}

void vkoSwapChain::configSwapChain(VkSurfaceFormatKHR& surfaceFormat, VkPresentModeKHR& presentMode, VkExtent2D& extent, const std::shared_ptr<vkoWindow>& window, const SwapChainSupportDetails& supportedProperties)
{
    surfaceFormat = setSurfaceFormat(supportedProperties.formats);
    presentMode = setPresentMode(supportedProperties.presentModes);
    extent = setExtent(supportedProperties.capabilities, window);

    swapChainImageFormat = surfaceFormat.format;
    swapChainExtent = extent;
}

void vkoSwapChain::DestroySwapChain()
{
    vkDestroySwapchainKHR(device, swapChain, nullptr);
}

VkSurfaceFormatKHR vkoSwapChain::setSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
    for (const auto& availableFormat : availableFormats) {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormat;
        }
    }
    return availableFormats[0];
}

VkPresentModeKHR vkoSwapChain::setPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
{
    for (const auto& availablePresentMode : availablePresentModes) {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
            return availablePresentMode;
        }
    }
    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D vkoSwapChain::setExtent(const VkSurfaceCapabilitiesKHR& capabilities, const std::shared_ptr<vkoWindow>& window)
{
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return capabilities.currentExtent;
    }
    else {
        int width, height;
        glfwGetFramebufferSize(window->getWindow(), &width, &height);

        VkExtent2D actualExtent = {
            static_cast<uint32_t>(width),
            static_cast<uint32_t>(height)
        };

        actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

        return actualExtent;
    }
}


