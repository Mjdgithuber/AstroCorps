#include <iostream>

#include "Application.h"
#include "..\xml\tinyxml2.h"


using namespace tinyxml2;
#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

int main() {
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile("SavedData.xml");
	XMLCheckResult(eResult);

	//Application::start_application();

	std::cin.get();

	return 0;
}