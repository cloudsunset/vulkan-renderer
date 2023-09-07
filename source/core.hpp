#pragma once
#include "window.hpp"
#include <vector>


const std::vector<const char*> validationLayers =
{ 
	"VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else 
const bool enableValidationLayers = true;
#endif




class Engine
{
public:

	Engine();
	~Engine();

	void Run();


private:

	const int width = 800;
	const int height = 640;

	VkInstance _instance;
	VkDebugUtilsMessengerEXT debugMessenger;

	vkoWindow _window{ width, height, "Vulkan Engine" };

	void BuildInstance();

	void BuildDebugMessenger();

	bool checkValidationLayerSupport();

	std::vector<const char*> getRequiredExtensions();

	void enumerateExtensions();

	

};

