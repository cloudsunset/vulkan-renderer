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
	device = std::make_shared<vkoDevice>(instance->get(), window->getSurface());
	swapChain = std::make_shared<vkoSwapChain>(device, window);
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
