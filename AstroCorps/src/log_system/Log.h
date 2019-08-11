#ifndef __LOG__H__
#define __LOG__H__

#include <memory>

#include "spdlog/spdlog.h"

class Log {
private:
	static std::shared_ptr<spdlog::logger> s_logger;
public:
	static void init();

	inline static std::shared_ptr<spdlog::logger>& get_logger() { return s_logger; }
};

#define LOG_INFO(...) Log::get_logger()->info(__VA_ARGS__)
#define LOG_DEBUG(...) Log::get_logger()->debug(__VA_ARGS__)
#define LOG_TRACE(...) Log::get_logger()->trace(__VA_ARGS__)
#define LOG_WARN(...) Log::get_logger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) Log::get_logger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) Log::get_logger()->critical(__VA_ARGS__)

#endif