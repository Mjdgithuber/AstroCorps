#if 0

#include <iostream>
#include <SFML/Graphics.hpp>

#define SOL_ALL_SAFETIES_ON 1
#include "Core.h"
#include "OldApplication.h"
#include "engine/tools/libs/lua/include/sol.hpp"
#include "lua_interface/LuaTest.h"
#include "lua_interface/user_types/entity/Entity.h"
#include <filesystem>

sol::protected_function_result check_valid(lua_State*, sol::protected_function_result result) {
	return result;
}

int main() {
	std::string path = "assets/scripts/";
	for (const auto & entry : std::filesystem::directory_iterator(path))
		std::cout << entry.path() << std::endl;

	// start and run the application
	OldApplication::start_application(36, 3);
	//Log::init();
	Lua::init();
	Lua::start("assets/scripts/main.lua");

	


	//std::cin.get();
	return 0;

	sf::Clock elto;

	/*for (int i = 0; i < 10; i++)
		std::cout << "Emma\n";
	std::cout << "Time: " << elto.getElapsedTime().asSeconds() << "\n";
	std::cin.get(); */
	// 2.73 3.26 3.33

	

	sol::state lua;

	lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string, sol::lib::table);

	std::cout << "Testing Lua API\n===========================\n";
	//lua.script_file("assets/scripts/test.luax");

	auto result = lua.script_file("assets/scripts/test.lua", &check_valid);

	sol::error err = result;

	std::cout << "\n\nDone\n===========================\n";

	std::cout << "Result == " << result.valid() << "\n";
	std::cout << "What? " << err.what() << "\n";

	std::cout << "Time: " << elto.getElapsedTime().asSeconds() << "\n";

	/*lua.script(R"(
				print('bark bark bark!')
				print('hello emma')
				print('femma'))"); */
	
	/*std::string a = lua.script(R"(
				print('bark bark bark!')
				print('hello emma')
				print('femma')
				return 'emma'
	)");
	std::cout << "Return \'" << a << "\'\n";

	int x = lua.script("return 5");
	std::cout << x << "\n"; */

	std::cout << "\n\n***** Program Finished. Press Enter! *****\n";
	std::cin.get();

	return 0;
}

#endif