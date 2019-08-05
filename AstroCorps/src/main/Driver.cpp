#include <iostream>

#include "Application.h"
#include "..\xml\tinyxml2.h"

// DELETE THIS PLEASE
#include "..\managers\XMLManager.h"

using namespace tinyxml2;
#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

int main() {
	//bool res = XML::load_map_data("Testing/femma.sv");
	//std::cout << "Result: " << res << "\n";


	Application::start_application();

	std::cin.get();

	return 0;
}