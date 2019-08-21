#ifndef __LOG__HPP__
#define __LOG__HPP__

template <typename... Args>
static bool Log::log_if(bool condition, unsigned int level, const std::string& message, Args... args) {
	if (!condition) return false;

	switch (level) {
	case INFO_LEVEL:
		LOG_INFO(message, args...);
		break;
	case DEBUG_LEVEL:
		LOG_DEBUG(message, args...);
		break;
	case TRACE_LEVEL:
		LOG_TRACE(message, args...);
		break;
	case WARN_LEVEL:
		LOG_WARN(message, args...);
		break;
	case ERROR_LEVEL:
		LOG_ERROR(message, args...);
		break;
	case CRIT_LEVEL:
		LOG_CRITICAL(message, args...);
		break;
	default:
		LOG_WARN("Attempt to use log_if with message '{0}' with invlaid level '{1}'",
			message, level);
		break;
	}

	return true;
}

#endif