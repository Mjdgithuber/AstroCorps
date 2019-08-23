#include "EngineFunctionality.h"
#include "engine/common.h"

namespace Lua {
	namespace EngineFunctionality {
		/* =========================================================== */
		/* ====================== Main Function ====================== */
		/* =========================================================== */
		
		namespace {
			/* Will give Lua access to use SPDLog to log to console */
			void register_print_utilites(sol::state& state) {
				// register every different type
				state["INFO"] = [](const std::string& str) { LOG_LUA_INFO(str); };
				state["DEBUG"] = [](const std::string& str) { LOG_LUA_DEBUG(str); };
				state["TRACE"] = [](const std::string& str) { LOG_LUA_TRACE(str); };
				state["WARN"] = [](const std::string& str) { LOG_LUA_WARN(str); };
				state["ERROR"] = [](const std::string& str) { LOG_LUA_ERROR(str); };
				state["CRIT"] = [](const std::string& str) { LOG_LUA_CRITICAL(str); };
			}

			/* Allows Lua scripts to update Application's tile map */
			void register_application_utilites(sol::state& state) {
				// give access to load_tile_map func in Application
				state["load_tile_map"] = &Application::load_tile_map;
			}

			/* Registers Direction in Lua script to ensure they
			   are synchronized with each other */
			void register_direction_utilities(sol::state& state) {
				state["STATIONARY"] = Engine::Util::STATIONARY;
				state["NORTH"] = Engine::Util::NORTH;
				state["EAST"] = Engine::Util::EAST;
				state["SOUTH"] = Engine::Util::SOUTH;
				state["WEST"] = Engine::Util::WEST;
			}
		}

		/* Register Engine Functions */
		void register_with_lua(sol::state& state) {
			register_print_utilites(state);
			register_application_utilites(state);
			register_direction_utilities(state);
		}
	}
}