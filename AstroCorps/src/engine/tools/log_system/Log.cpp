#include "Log.h"
#include "engine/tools/libs/spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> Log::s_logger;
std::shared_ptr<spdlog::logger> Log::s_lua_logger;

/* Setup both loggers and their formatting */
void Log::init() {
	// set formatting of logged messages
	spdlog::set_pattern("%^[%T][%n][%l]: %v%$");

	// engine logger
	s_logger = spdlog::stdout_color_mt("ENGINE");
	s_logger->set_level(spdlog::level::trace);

	// logger used in scripts
	s_lua_logger = spdlog::stdout_color_mt("LUA");
	s_lua_logger->set_level(spdlog::level::trace);
}