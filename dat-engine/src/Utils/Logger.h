#pragma once

#include <spdlog/spdlog.h>

namespace dat
{
	inline void initializeLogger()
	{
#if defined(_DEBUG)
		spdlog::set_level(spdlog::level::trace);
#endif
	}
}

#if defined(_DEBUG) || defined(NDEBUG)
	#define DAT_CORE_WARN(...)		::spdlog::warn(__VA_ARGS__)
	#define DAT_CORE_ERROR(...)		::spdlog::error(__VA_ARGS__)
	#define DAT_CORE_CRITICAL(...)	::spdlog::critical(__VA_ARGS__)
#else
	#define DAT_CORE_WARN(...)
	#define DAT_CORE_ERROR(...)
	#define DAT_CORE_CRITICAL(...)
#endif

#if defined(_DEBUG)
	#define DAT_CORE_DEBUG(...)		::spdlog::debug(__VA_ARGS__)
	#define DAT_CORE_TRACE(...)		::spdlog::trace(__VA_ARGS__)
	#define DAT_CORE_INFO(...)		::spdlog::info(__VA_ARGS__)

#else
	#define DAT_CORE_TRACE(...)
	#define DAT_CORE_INFO(...)
	#define DAT_CORE_WARN(...)
	#define DAT_CORE_ERROR(...)
#endif