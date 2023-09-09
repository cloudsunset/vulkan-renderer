#pragma once

#include <vulkan/vulkan.h>
#include <iostream>

class vkoInstance
{
public:

	vkoInstance(const char* instance_name);
	~vkoInstance();


private:

	void BuildInstance(const char* instance_name);

	VkInstance m_Instance;
	VkDebugUtilsMessengerEXT m_DebugMessenger;

};