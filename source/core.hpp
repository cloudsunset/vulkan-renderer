#pragma once
#include "window.hpp"
#include "device.hpp"
#include "instance.hpp"
#include "swapchain.hpp"
#include "pipeline.hpp"
#include <vector>
#include <glm/glm.hpp>

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
	std::unique_ptr<vkoDevice> device;
	std::unique_ptr<vkoSwapChain>  swapChain;
	std::unique_ptr<vkoPipeline>  pipeline;

	std::vector<VkCommandBuffer> commandBuffers;
	VkPipelineLayout pipelineLayout;

	void createPipelineLayout();
	void createPipeline();

	void createCommandBuffer();
	void recordCommandBuffer(uint32_t imageIndex);

	void drawFrame();

	void destroyPipelineLayout();
	void destroyRenderer();

};

