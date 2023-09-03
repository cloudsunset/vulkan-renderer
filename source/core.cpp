#include "core.hpp"

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::BuildWindow()
{
}

void Engine::Run()
{
	while (!_vkoWindow.shouldClose())
	{
		glfwPollEvents();
		
	}
}
