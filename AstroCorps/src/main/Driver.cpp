#include <iostream>

#include "Application.h"

int main() {
	// start and run the application
	Application::start_application(36, 3);

	std::cout << "\n\n***** Program Finished. Press Enter! *****\n";
	std::cin.get();

	return 0;
}