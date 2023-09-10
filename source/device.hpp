#pragma once
#include "window.hpp"
#include <optional>


//struct QueueFamilyIndices
//{
//	uint32_t graphicsFamily;
//	uint32_t presentFamily;
//	bool graphicsFamilyHasValue = false;
//	bool presentFamilyHasValue = false;
//	bool isComplete() { return graphicsFamilyHasValue; }
//	//bool isComplete() { return graphicsFamilyHasValue && presentFamilyHasValue; }
//};

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;

	bool isComplete() {
		return graphicsFamily.has_value();
	}
};

class vkoDevice
{
public:

	vkoDevice(VkInstance &instance, vkoWindow &window);
	~vkoDevice();

	VkPhysicalDeviceProperties properties;

private:

	VkInstance &_instance;
	vkoWindow &_window;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice _device;
	

	void BuildPhysicalDevice();

	bool VerifyDevice(VkPhysicalDevice device);

	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

};