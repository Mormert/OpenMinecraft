#include "engine.h"

#include <exception>
#include <iostream>

int main()
{
	Engine engine;

	try {
		engine.Start();
		engine.Run();
	}
	catch (std::exception e){
		std::cerr << "An uncaught error occured: " << e.what() << "\n";
		exit(1);
	}

	return 0;
}