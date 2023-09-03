#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

class vkoWindow
{

public:

	vkoWindow(int w, int h, std::string name);
	~vkoWindow();

	bool shouldClose() { return glfwWindowShouldClose(window); }


private:

	void BuildWindow();

	int width = 0;
	int height = 0;

	std::string windowName;
	GLFWwindow* window = nullptr;

};
