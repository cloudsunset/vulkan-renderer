#pragma once
#include <vulkan/vulkan.h>
#include "device.hpp"
#include <vector>
#include <string>

class vkoPipeline
{
public:
	vkoPipeline(VkDevice& device);
	~vkoPipeline();

private:

	static std::vector<char> readFile(const std::string& filePath);
	 
	void createGraphicsPipeline();

	VkShaderModule createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

	VkPipeline graphicsPipeline = VK_NULL_HANDLE;
	VkPipelineLayout pipelineLayout;
	VkDevice& device;

	VkShaderModule vertexShaderModule = VK_NULL_HANDLE;
	VkShaderModule fragmentShaderModule = VK_NULL_HANDLE;



};