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

	vkoWindow _vkoWindow{ width, height, "Vulkan Engine" };

	void BuildWindow();

	

};

