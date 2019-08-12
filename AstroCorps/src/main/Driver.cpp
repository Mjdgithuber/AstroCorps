#include <iostream>

a#include "Application.h"
#include "libs/sol/sol.hpp"

int main() {
	// start and run the application
	Application::start_application(36, 3);

	sol::state lua;

	lua.open_libraries(sol::lib::base, sol::lib::package);
	std::string a = lua.script(R"(
				print('bark bark bark!')
				print('hello emma')
				print('femma')
				return 'emma'
	)");
	std::cout << "Return \'" << a << "\'\n";

	int x = lua.script("return 5");
	std::cout << x << "\n";

	std::cout << "\n\n***** Program Finished. Press Enter! *****\n";
	std::cin.get();

	return 0;
}