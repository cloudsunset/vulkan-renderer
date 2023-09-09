#include "core.hpp"
#include <stdexcept>
#include <vector>
#include <iostream>
#include <cstring>
#include "vlayers.hpp"

Engine::Engine()
{
	// check validatio layers
}

Engine::~Engine()
{

}


//void Engine::checkGPU()
//{
//	uint32_t deviceCount = 0;
//
//	if (vkEnumeratePhysicalDevices(_instance, &deviceCount, nullptr) != VK_SUCCESS)
//	{
//		throw std::runtime_error("vkEnumeratePhysicalDevices failed");
//	}
//
//	if (deviceCount == 0) {
//		throw std::runtime_error("No GPUs with Vulkan support!");
//	}
//	std::cout << "Device count: " << deviceCount << std::endl;
//	std::vector<VkPhysicalDevice> devices(deviceCount);
//	vkEnumeratePhysicalDevices(_instance, &deviceCount, devices.data());
//
//	for (const auto& device : devices) {
//		if (VerifyDevice(device)) {
//			physicalDevice = device;
//			break;
//		}
//	}
//
//	if (physicalDevice == VK_NULL_HANDLE) {
//		throw std::runtime_error("failed to find a suitable GPU!");
//	}
//
//	vkGetPhysicalDeviceProperties(physicalDevice, &properties);
//	std::cout << "physical device: " << properties.deviceName << std::endl;
//}

void Engine::Run()
{
	while (!_window.shouldClose())
	{
		glfwPollEvents();
		
	}
}
