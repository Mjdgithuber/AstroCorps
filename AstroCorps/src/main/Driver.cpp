#include <iostream>

#include "Application.h"
//#include "..\xml\tinyxml2.h"

// DELETE THIS PLEASE
#include "..\managers\XMLManager.h"

int main() {
	//delete XML::load_map("assets/testing/xmltest.xml");


	Application::start_application(36, 3);

	std::cout << "\n\n***** Program Finished. Press Enter! *****\n";
	std::cin.get();
	

	return 0;
}