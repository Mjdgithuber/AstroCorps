#ifndef __LOG__H__
#define __LOG__H__

#include <memory>

#include "libs/spdlog/spdlog.h"

class Log {
private:
	static std::shared_ptr<spdlog::logger> s_logger;
	static std::shared_ptr<spdlog::logger> s_lua_logger;
public:
	static void init();

	inline static std::shared_ptr<spdlog::logger>& get_logger() { return s_logger; }
	inline static std::shared_ptr<spdlog::logger>& get_lua_logger() { return s_lua_logger; }
};

#define LOG_INFO(...) Log::get_logger()->info(__VA_ARGS__)
#define LOG_DEBUG(...) Log::get_logger()->debug(__VA_ARGS__)
#define LOG_TRACE(...) Log::get_logger()->trace(__VA_ARGS__)
#define LOG_WARN(...) Log::get_logger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) Log::get_logger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) Log::get_logger()->critical(__VA_ARGS__)

#define LOG_LUA_INFO(...) Log::get_lua_logger()->info(__VA_ARGS__)
#define LOG_LUA_DEBUG(...) Log::get_lua_logger()->debug(__VA_ARGS__)
#define LOG_LUA_TRACE(...) Log::get_lua_logger()->trace(__VA_ARGS__)
#define LOG_LUA_WARN(...) Log::get_lua_logger()->warn(__VA_ARGS__)
#define LOG_LUA_ERROR(...) Log::get_lua_logger()->error(__VA_ARGS__)
#define LOG_LUA_CRITICAL(...) Log::get_lua_logger()->critical(__VA_ARGS__)

#endif