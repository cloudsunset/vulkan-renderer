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

	// TODO solve device class conversion problem / maybe substiture window class for surface in arguments of device constructor

	const char* instance_name = "Vulkan Renderer";
	const int width = 800;
	const int height = 640;
	// preciso criar a surface na window e a surface precisa da instance mas a window e criada antes da instance

	std::shared_ptr<vkoWindow>  window;

	std::shared_ptr<vkoInstance>  instance;

	// m_Instance.get(), _window
	
	std::unique_ptr<vkoDevice> device;

};

