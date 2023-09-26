#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>
#include "instance.hpp"

class vkoWindow
{

public:

	vkoWindow(int w, int h);
	~vkoWindow();

	bool shouldClose() { return glfwWindowShouldClose(window); }

	inline GLFWwindow* getWindow() { return window; }
	inline VkSurfaceKHR getSurface(){ return surface; }

	void BuildWindow();
	void createSurface(VkInstance& instance);

	void destroySurface(VkInstance& instance);
	void destroyWindow();

private:

	
	

	int width = 0;
	int height = 0;

	std::string windowName;
	GLFWwindow* window = nullptr;

	VkSurfaceKHR surface;

};
