#ifndef __ENGINE__FUNCTIONALITY__H__
#define __ENGINE__FUNCTIONALITY__H__

#include "engine/tools/libs/lua/include/sol.hpp"

namespace Lua {
	namespace EngineFunctionality {
		/* =========================================================== */
		/* ====================== Main Function ====================== */
		/* =========================================================== */
		////////////////////////////////////////////////////////////
		/// This will register engine functionality for use in Lua 
		/// scripts
		/// Params:
		/// state- The main Lua state
		////////////////////////////////////////////////////////////
		void register_with_lua(sol::state& state);
	}
}

#endif