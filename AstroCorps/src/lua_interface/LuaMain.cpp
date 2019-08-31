#include "LuaMain.h"
#include "engine/tools/libs/lua/include/sol.hpp"
#include "engine_functionality/EngineFunctionality.h"
#include "user_types/parser/XMLParser.h"
#include "user_types/directory/Directory.h"
#include "user_types/entity/Entity.h"
#include "user_types/tile_map/TileMap.h"
#include "engine/core/Application.h"

namespace Lua {
	namespace {
		const char* const SCRIPT_FOLDER = "scripts/";
		sol::state lua_state;

		/* Checks to see if script file is well formed */
		sol::protected_function_result check_valid(lua_State*, sol::protected_function_result result) {
			return result;
		}
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

	void init() {
		// open common libraries for lua use
		lua_state.open_libraries(
			sol::lib::base, 
			sol::lib::package, 
			sol::lib::string, 
			sol::lib::table);

		// register load_file function
		lua_state["load_file"] = &load_script;

		EngineFunctionality::register_with_lua(lua_state);
		XMLParser::register_with_lua(lua_state);
		Directory::register_with_lua(lua_state);
		Entity::register_with_lua(lua_state);
		TileMap::register_with_lua(lua_state);
	}
	
	void start(const char* path) {
		load_script("main.lua");
	}

	void lost_focus() {
		// set all keys to be unpressed
		for(unsigned int i = 0; i < 26; i++)
			lua_state["update_keyboard"]((char)(65 + i), false);
	}

	void process_key(sf::Keyboard::Key code, bool pressed) {
		/* calls update_keyboard in Lua. NOTE: 65 + code
		   converts the Key into it's char representation
		   65 is the char 'A', the Key A is equal to 0 */
		lua_state["update_keyboard"]((char)(65 + code), pressed);
	}

	void update() {
		lua_state["GameManager"]["update_game"]();
	}

}