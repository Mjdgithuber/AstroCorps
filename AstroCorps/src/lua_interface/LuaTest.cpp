#include "LuaTest.h"
#include "engine/tools/libs/lua/include/sol.hpp"
#include "user_types/parser/LuaXMLParser.h"
#include "user_types/directory/Directory.h"
#include "user_types/entity/Entity.h"

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

		void register_print_utilites() {
			// register every different type
			lua_state["info"] = [](const std::string& str) { LOG_LUA_INFO(str); };
			lua_state["debug"] = [](const std::string& str) { LOG_LUA_DEBUG(str); };
			lua_state["trace"] = [](const std::string& str) { LOG_LUA_TRACE(str); };
			lua_state["warn"] = [](const std::string& str) { LOG_LUA_WARN(str); };
			lua_state["error"] = [](const std::string& str) { LOG_LUA_ERROR(str); };
			lua_state["critical"] = [](const std::string& str) { LOG_LUA_CRITICAL(str); };
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

		void register_entity_type() {
			sol::usertype<Entity> entity_type = lua_state.new_usertype<Entity>("Entity",
				// send in the usable constructors
				sol::constructors<Entity(int x, int y, int width, int height, const std::string& name)>());

			entity_type["get_x"] = &Entity::get_x;
			entity_type["get_y"] = &Entity::get_y;
		}
	}

	void init() {
		// open common libraries for lua use
		lua_state.open_libraries(
			sol::lib::base, 
			sol::lib::package, 
			sol::lib::string, 
			sol::lib::table);

		register_print_utilites();
		register_file_utilites();
		register_parser_utilities();
		register_entity_type();
	}

	Entity* test;
	void update(Entity* newTest) {
		test = newTest;
		LOG_ERROR("NExt Line");
		std::cout << test->get_x() << "\n";
	}

	
	void start(const char* path) {
		lua_state["update"] = &update;
		load_script("main.lua");

		Entity* emma = lua_state["player"];
		std::cout << "Femma: " << emma << "\n";
		std::cout << "X: " << emma->get_x() << "\n";

		lua_state["femma"]();
		std::cout << "Yettle\n";
		Entity* femma = lua_state["player"];
		std::cout << "Femma: " << femma << "\n";

		//for (int i = 0; i < 10000; i++) { lua_state["random"](); LOG_INFO("kelto"); };

		std::cout << "X: " << emma->get_x() << "\n";
		lua_state["elto"]();
		std::cin.get();
		//LOG_DEBUG("Emma: {0}", "");
	}

}