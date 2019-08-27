#ifndef __LOG__H__
#define __LOG__H__

#include <memory>

#include "engine/tools/libs/spdlog/spdlog.h"

namespace Engine {
	class Log {
	private:
		static std::shared_ptr<spdlog::logger> s_logger;
		static std::shared_ptr<spdlog::logger> s_lua_logger;
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& get_logger() { return s_logger; }
		inline static std::shared_ptr<spdlog::logger>& get_lua_logger() { return s_lua_logger; }


		template <unsigned int LV, typename... Args>
		static bool log_if(bool condition, const std::string& message, Args... args);
	};
}

/* Macros to both simply logging and allow removal
   of all logging features when released to ensure
   that no extra overhead affects runtime */

#define INFO_LEVEL   0
#define DEBUG_LEVEL  1
#define TRACE_LEVEL  2
#define WARN_LEVEL   3
#define ERROR_LEVEL  4
#define CRIT_LEVEL   5

#define LOG_INFO(...)         Engine::Log::get_logger()->info(__VA_ARGS__)
#define LOG_DEBUG(...)        Engine::Log::get_logger()->debug(__VA_ARGS__)
#define LOG_TRACE(...)        Engine::Log::get_logger()->trace(__VA_ARGS__)
#define LOG_WARN(...)         Engine::Log::get_logger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)        Engine::Log::get_logger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)     Engine::Log::get_logger()->critical(__VA_ARGS__)

/* LOG_IF_AR - Automatically will return false if the condition
     is true, the message gets logged before it returns.
   LOG_IF - Just logs the message if the condition is true and
     will not automatically return anything
   USAGE:
     LOG_IF('LEVEL', 'MESSAGE TO LOG', '...');
     'LEVEL' - The level to log at like INFO_LEVEL & ERROR_LEVEL
     'MESSAGE TO LOG' - E.G. "This is a message {0}, yep {1}"
     '...' - {number} gets replaced with trailing paramters */
#define LOG_IF_AR(level, ...) if(Engine::Log::log_if<level>(__VA_ARGS__)) return false
#define LOG_IF(level, ...)    Engine::Log::log_if<level>(__VA_ARGS__)

#define LOG_LUA_INFO(...)     Engine::Log::get_lua_logger()->info(__VA_ARGS__)
#define LOG_LUA_DEBUG(...)    Engine::Log::get_lua_logger()->debug(__VA_ARGS__)
#define LOG_LUA_TRACE(...)    Engine::Log::get_lua_logger()->trace(__VA_ARGS__)
#define LOG_LUA_WARN(...)     Engine::Log::get_lua_logger()->warn(__VA_ARGS__)
#define LOG_LUA_ERROR(...)    Engine::Log::get_lua_logger()->error(__VA_ARGS__)
#define LOG_LUA_CRITICAL(...) Engine::Log::get_lua_logger()->critical(__VA_ARGS__)

/* Contains defition of log_if function */
#include "Log.hpp"

#endif