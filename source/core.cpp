#include "core.hpp"
#include <stdexcept>
#include <vector>
#include <iostream>
#include <cstring>
#include "vlayers.hpp"

Engine::Engine()
{
	// check validatio layers
}

Engine::~Engine()
{

}

void Engine::Run()
{
	while (!_window.shouldClose())
	{
		glfwPollEvents();
		
	}
}
