#include "window.hpp"

vkoWindow::vkoWindow(int w, int h, std::string name) : width{w}, height{h}, windowName{name}
{
	BuildWindow();
}

vkoWindow::~vkoWindow()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void vkoWindow::BuildWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);

}
