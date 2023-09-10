#pragma once
#include "window.hpp"
#include "device.hpp"
#include "instance.hpp"
#include <vector>

struct EngineConfigInfo
{
	const int width;
	const int height;
	const char* Enginename;

};

class Engine
{
public:

	Engine();
	~Engine();

	void Run();


private:

	const char* instance_name = "Vulkan Engine";

	const int width = 800;
	const int height = 640;

	vkoWindow _window{ width, height, instance_name };
	vkoInstance m_Instance{ instance_name };
	vkoDevice m_Device{ m_Instance.get(), _window};


	// make sure instance is created before device
	//vkoDevice _device;

	//void checkGPU();


	

};

