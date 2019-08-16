#include "Log.h"
#include "engine/tools/libs/spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> Log::s_logger;
std::shared_ptr<spdlog::logger> Log::s_lua_logger;

void Log::init() {
	// engine logger
	s_logger = spdlog::stdout_color_mt("Engine");
	s_logger->set_level(spdlog::level::trace);
	s_logger->set_pattern("%^[%T] %n: %v%$");

	// logger used in scripts
	s_lua_logger = spdlog::stdout_color_mt("Lua");
	s_lua_logger->set_level(spdlog::level::trace);
	s_lua_logger->set_pattern("%^[%T][%l] %n: %v%$");
}