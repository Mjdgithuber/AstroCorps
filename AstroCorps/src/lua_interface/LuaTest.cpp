#include "LuaTest.h"
#include "libs/sol/sol.hpp"
#include "lua_interface/tools/parser/LuaXMLParser.h"
#include "lua_interface/tools/file_system/Directory.h"

namespace Lua {

	namespace {
		const char* const SCRIPT_FOLDER = "assets/scripts/";
		sol::state lua_state;

		sol::protected_function_result check_valid(lua_State*, sol::protected_function_result result) {
			return result;
		}
		
		bool load_script(const std::string& script_file) {
			// try to load script
			LOG_INFO("Loading Script File: '{0}'", script_file);
			auto result = lua_state.script_file(SCRIPT_FOLDER + script_file, &check_valid);

			// check for errors in script
			if (!result.valid()) {
				// wrap result in error & print
				sol::error err = result;
				LOG_ERROR("{0}", err.what());
				return false;
			}
			return true;
		}

		void register_file_utilites() {
			// register load_file function
			lua_state["load_file"] = &load_script;

			// register directory user-type
			sol::usertype<Directory> dir_type = lua_state.new_usertype<Directory>("Directory",
				// send in the usable constructors
				sol::constructors<Directory(), Directory(const std::string&)>());

			// register directory functions
			dir_type["open_dir"] = &Directory::open_dir;
			dir_type["is_open"] = &Directory::is_open;
			dir_type["number_of_files"] = &Directory::number_of_files;
			dir_type["get_filename"] = &Directory::get_filename;
		}

		void register_parser_utilities() {
			// allow the parser class to be accessed by scripts
			sol::usertype<LuaXMLParser> parser_type = lua_state.new_usertype<LuaXMLParser>("Parser",
				// send in the usable constructors
				sol::constructors<LuaXMLParser(std::string)>());

			// register parser's main functions
			parser_type["open_document"] = &LuaXMLParser::open_doc;
			parser_type["cache_root_element"] = &LuaXMLParser::cache_root_element;
			parser_type["cache_element"] = &LuaXMLParser::cache_element;

			// overloading cache_child_element
			bool (LuaXMLParser::*default_child)(void) = &LuaXMLParser::cache_child_element;
			bool (LuaXMLParser::*search_child)(const char*) = &LuaXMLParser::cache_child_element;
			parser_type["cache_child_element"] = sol::overload(search_child, default_child);

			// register attribute checker
			parser_type["check_attribute"] = &LuaXMLParser::check_attribute;

			// register attribute getters
			parser_type["float_attribute"] = &LuaXMLParser::get_attribute<float>;
			parser_type["int_attribute"] = &LuaXMLParser::get_attribute<int>;
			parser_type["string_attribute"] = &LuaXMLParser::get_attribute<std::string>;

			//parser_type["cach_next_sibling_element"] = &LuaXMLParser::cache_next_sibling_element;
		}
	}

	void init() {
		// open common libraries for lua use
		lua_state.open_libraries(
			sol::lib::base, 
			sol::lib::package, 
			sol::lib::string, 
			sol::lib::table);

		register_file_utilites();
		register_parser_utilities();
	}

	void start(const char* path) {
		load_script("main.lua");
	}

}