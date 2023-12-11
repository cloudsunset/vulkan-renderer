#include "core.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main()
{
	Engine engine{};

	try
	{
		engine.Run();
	}
	catch(const std::exception &e)
	{
		std::cerr << e.what() << "\n";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
