#pragma once

#include "window.hpp"

class Engine
{
public:
	Engine();
	~Engine();

	void Run();

private:
	bool isDebug = true;

	const int width = 800;
	const int height = 640;

	VkInstance _instance;

	vkoWindow _window{ width, height, "Vulkan Engine" };

	void BuildInstance();

	//void BuildWindow();

	

};

