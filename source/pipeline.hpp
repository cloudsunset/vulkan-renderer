#pragma once
#include <vulkan/vulkan.h>
#include "device.hpp"
#include <vector>
#include <string>

struct PipelineConfigInfo
{
	VkPipelineLayout pipelineLayout = nullptr;
	VkRenderPass renderPass = nullptr;

};

class vkoPipeline
{
public:
	vkoPipeline(VkDevice& device, PipelineConfigInfo& pipelineConfig);
	~vkoPipeline();

	vkoPipeline(const vkoPipeline&) = delete;
	vkoPipeline& operator=(const vkoPipeline&) = delete;

	VkPipeline& getGraphicsPipeline();

	void bind(VkCommandBuffer commandBuffer);

	void DestroyPipeline();

private:

	static std::vector<char> readFile(const std::string& filePath);
	 
	void createGraphicsPipeline(PipelineConfigInfo& pipelineConfig);

	VkShaderModule createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

	VkPipeline graphicsPipeline = VK_NULL_HANDLE;

	VkDevice& device;

	VkShaderModule vertexShaderModule = VK_NULL_HANDLE;
	VkShaderModule fragmentShaderModule = VK_NULL_HANDLE;

};