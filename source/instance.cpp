#include "instance.hpp"
#include "vlayers.hpp"
#include "vextensions.hpp"
#include <stdexcept>

vkoInstance::vkoInstance(const char* instance_name)
{
	BuildInstance(instance_name);
}

vkoInstance::~vkoInstance()
{

	std::cout << "destructors" << std::endl;
	if (vlayers::enableValidationLayers)
	{
		vlayers::DestroyDebugUtilsMessengerEXT(m_Instance, m_DebugMessenger, nullptr);
		std::cout << "DestroyDebugUtilsMessengerEXT" << std::endl;
	}


	vkDestroyInstance(m_Instance, nullptr);
}

VkInstance& vkoInstance::get()
{
	return m_Instance;
}

void vkoInstance::BuildInstance(const char* instance_name)
{
	if (vlayers::enableValidationLayers && !vlayers::checkValidationLayerSupport()) {
		throw std::runtime_error("validation layers requested, but not available!");
	}

	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = instance_name;
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "Engine A";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	auto extensions = vext::getRequiredExtensions();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};

	if (vlayers::enableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(vlayers::validationLayers.size());
		createInfo.ppEnabledLayerNames = vlayers::validationLayers.data();

		vlayers::populateDebugMessengerCreateInfo(debugCreateInfo);
		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
	}
	else
	{
		createInfo.enabledLayerCount = 0;

		createInfo.pNext = nullptr;
	}

	vext::enumerateExtensions();

	// validation layers

	if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create instance!");
	}

	vlayers::BuildDebugMessenger(m_Instance, m_DebugMessenger);

}




