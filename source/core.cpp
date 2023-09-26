#include "core.hpp"
#include <stdexcept>
#include <vector>
#include <iostream>
#include <cstring>
#include "vlayers.hpp"

Engine::Engine()
{
	window = std::make_shared<vkoWindow>(width, height);
	instance = std::make_shared<vkoInstance>(instance_name);
	window->createSurface(instance->get());
	VkSurfaceKHR S = window->getSurface();
	device = std::make_unique<vkoDevice>(instance->get(), S);

}

Engine::~Engine()
{

}

void Engine::Run()
{


	while (!window->shouldClose())
	{
		glfwPollEvents();
		
	}
}
