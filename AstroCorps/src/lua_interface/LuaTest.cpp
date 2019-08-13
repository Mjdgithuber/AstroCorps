#include "LuaTest.h"
#include "libs/sol/sol.hpp"
#include "xml/parsers/LuaXMLParser.h"

namespace Lua {

	namespace {
		sol::state lua_state;

		void register_utilities() {
			// allow the parser class to be accessed by scripts
			sol::usertype<LuaXMLParser> parser_type = lua_state.new_usertype<LuaXMLParser>("Parser",
				// send in the usable constructors
				sol::constructors<LuaXMLParser(std::string)>());

			// register parser's functions
			parser_type["open_document"] = &LuaXMLParser::open_doc;
			parser_type["find_element"] = &LuaXMLParser::find_element;
		}

		sol::protected_function_result check_valid(lua_State*, sol::protected_function_result result) {
			return result;
		}
	}

	void init() {
		// open common libraries for lua use
		lua_state.open_libraries(
			sol::lib::base, 
			sol::lib::package, 
			sol::lib::string, 
			sol::lib::table);

		register_utilities();
	}

	void start(const char* path) {
		auto result = lua_state.script_file(path, &check_valid);

		sol::error err = result;

		std::cout << "\n\nDone\n===========================\n";

		std::cout << "Result == " << result.valid() << "\n";
		std::cout << "What? " << err.what() << "\n";
	}

}