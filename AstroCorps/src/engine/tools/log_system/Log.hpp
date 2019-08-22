#ifndef __LOG__HPP__
#define __LOG__HPP__

template <unsigned int LV, typename... Args>
static bool Log::log_if(bool condition, const std::string& message, Args... args) {
	// exit immediately if no logging is needed
	if (!condition) return false;

	/* constxpr is used to determine control path
	   at compile, so these if statements have no
	   runtime cost whatsoever */
	if constexpr (LV == INFO_LEVEL)
		LOG_INFO(message, args...);
	else if constexpr (LV == DEBUG_LEVEL)
		LOG_DEBUG(message, args...);
	else if constexpr (LV == TRACE_LEVEL)
		LOG_TRACE(message, args...);
	else if constexpr (LV == WARN_LEVEL)
		LOG_WARN(message, args...);
	else if constexpr (LV == ERROR_LEVEL)
		LOG_ERROR(message, args...);
	else if constexpr (LV == CRIT_LEVEL)
		LOG_CRITICAL(message, args...);
	else
		LOG_WARN("Attempt to use log_if with message '{0}' with invlaid level '{1}'",
			message, LV);

	// only return true if level if error or critical
	if constexpr (LV >= ERROR_LEVEL) return true;
	else return false;
}

#endif