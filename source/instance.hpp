#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>

class vkoInstance
{
public:

	vkoInstance(const char* instance_name);
	~vkoInstance();

	VkInstance& get();

	const char* instance_name = "instance name test";

private:

	void BuildInstance(const char* instance_name);
	void DestroyInstance();
	
	VkInstance m_Instance;
	VkDebugUtilsMessengerEXT m_DebugMessenger;

};