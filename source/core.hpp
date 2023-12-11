#pragma once
#include "window.hpp"
#include "device.hpp"
#include "instance.hpp"
#include "swapchain.hpp"
#include "pipeline.hpp"
#include <vector>

class Engine
{
public:

	Engine();
	~Engine();

	void Run();

private:

	const char* instance_name = "Vulkan Renderer";
	const int width = 800;
	const int height = 640;

	std::shared_ptr<vkoWindow>  window;
	std::shared_ptr<vkoInstance>  instance;
	std::shared_ptr<vkoDevice> device;
	std::shared_ptr<vkoSwapChain>  swapChain;

	std::shared_ptr<vkoPipeline>  pipeline;

	VkCommandBuffer commandBuffer;

	VkPipelineLayout pipelineLayout;

	void createPipelineLayout();
	void createPipeline();

	void createCommandBuffer();
	void recordComandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	void drawFrame();

	void destroyPipelineLayout();

	void destroyRenderer();

};

