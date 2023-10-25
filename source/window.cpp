#include "window.hpp"
#include <stdexcept>

vkoWindow::vkoWindow(int w, int h ) : width{w}, height{h}
{
	BuildWindow();
}

vkoWindow::~vkoWindow()
{
}

void vkoWindow::BuildWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
}

void vkoWindow::createSurface(VkInstance& instance)
{
	if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
		throw std::runtime_error("failed to create window surface!");
	}
}

void vkoWindow::destroyWindow()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void vkoWindow::destroySurface(VkInstance& instance)
{
	vkDestroySurfaceKHR(instance, surface, nullptr);
}
