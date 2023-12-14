#include "core.hpp"
#include <stdexcept>
#include <vector>
#include <iostream>
#include <cstring>
#include "vlayers.hpp"

Engine::Engine()
{
	window = std::make_shared<vkoWindow>(width, height);
	instance = std::make_shared<vkoInstance>(instance_name);
	window->createSurface(instance->get());
	device = std::make_shared<vkoDevice>(instance->get(), window->getSurface());
	swapChain = std::make_shared<vkoSwapChain>(device, window);

	createPipelineLayout();
	createPipeline();
	createCommandBuffer();
}

Engine::~Engine(){}

void Engine::createPipelineLayout()
{
	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 0; // Optional
	pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
	pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
	pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

	if (vkCreatePipelineLayout(device->getLogicalDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create pipeline layout!");
	}
}

void Engine::createPipeline()
{
	PipelineConfigInfo pipelineConfig{};
	pipelineConfig.renderPass = swapChain->getRenderPass();
	pipelineConfig.pipelineLayout = pipelineLayout;

	pipeline = std::make_shared<vkoPipeline>(device->getLogicalDevice(), pipelineConfig);
}

void Engine::createCommandBuffer()
{

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = device->getCommandPool();
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;

	if (vkAllocateCommandBuffers(device->getLogicalDevice(), &allocInfo, &commandBuffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}
	
}

void Engine::recordComandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex)
{
	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = 0; // Optional
	beginInfo.pInheritanceInfo = nullptr; // Optional

	if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
		throw std::runtime_error("failed to begin recording command buffer!");
	}

	VkRenderPassBeginInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = swapChain->getRenderPass();
	renderPassInfo.framebuffer = swapChain->getFrameBuffer(imageIndex);

	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = swapChain->getSwapChainExtent();

	VkClearValue clearColor = { {{0.749f, 0.f, 0.376f, 1.0f}} };
	renderPassInfo.clearValueCount = 1;
	renderPassInfo.pClearValues = &clearColor;

	vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		pipeline->bind(commandBuffer);

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(swapChain->getSwapChainExtent().width);
		viewport.height = static_cast<float>(swapChain->getSwapChainExtent().height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent = swapChain->getSwapChainExtent();

		vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

		vkCmdDraw(commandBuffer, 3, 1, 0, 0);
	
	
	vkCmdEndRenderPass(commandBuffer);

	if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to record command buffer!");

	}
}

void Engine::drawFrame()
{

	uint32_t imageIndex;
	auto result = swapChain->acquireNextImage(&imageIndex, commandBuffer);

	if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
	{
		throw std::runtime_error("Failed to adquire swap chain image");
	}

	vkResetCommandBuffer(commandBuffer, 0);

	recordComandBuffer(commandBuffer, imageIndex);

	
	result = swapChain->submitCommandBuffers(commandBuffer, &imageIndex, device->getGraphicsQueue(), device->getPresentQueue());

	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to adquire swap chain image");
	}
}

void Engine::destroyPipelineLayout()
{
	vkDestroyPipelineLayout(device->getLogicalDevice(), pipelineLayout, nullptr);
}

void Engine::destroyRenderer()
{

	swapChain->DestroySyncObjects();

	device->DestroyCommandPool();

	swapChain->DestroyFramebuffers();

	pipeline->DestroyPipeline();

	this->destroyPipelineLayout();

	swapChain->DestroyRenderPass();

	swapChain->DestroyImageViews();

	swapChain->DestroySwapChainKHR();

	device->DestroyLogicalDevice();

	instance->DestroyValidationLayer();

	window->destroySurface(instance->get());

	instance->DestroyInstance();

	window->destroyWindow();

}

void Engine::Run()
{
	while (!window->shouldClose())
	{
		glfwPollEvents();
		drawFrame();
	}

	vkDeviceWaitIdle(device->getLogicalDevice());
	destroyRenderer();
}


