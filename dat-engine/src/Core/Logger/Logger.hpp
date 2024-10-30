#pragma once
#include "Core/Defines.hpp"
#include "Core/NonCopyable.hpp"
#include "Core/Memory/Memory.hpp"

#pragma warning(push, 0)
	#include <spdlog/spdlog.h>
#pragma warning(pop)

namespace dat::logger
{
	inline dat_shared<spdlog::logger> MainLogger;
	inline dat_shared<spdlog::logger> InfoLogger;

	void InitializeLogger();
}

#ifdef DAT_DEBUG
	#define DAT_LOG_CRITICAL(...)	{ ::dat::logger::MainLogger->critical(__VA_ARGS__); DAT_BREAKPOINT(); }
	#define DAT_LOG_ERROR(...)		  ::dat::logger::MainLogger->error(__VA_ARGS__)
	#define DAT_LOG_WARN(...)		  ::dat::logger::MainLogger->warn(__VA_ARGS__)
	#define DAT_LOG_DEBUG(...)		  ::dat::logger::MainLogger->debug(__VA_ARGS__)
	#define DAT_LOG_TRACE(...)		  ::dat::logger::InfoLogger->trace(__VA_ARGS__)
	#define DAT_LOG_INFO(...)		  ::dat::logger::InfoLogger->info(__VA_ARGS__)

#else
	#define DAT_LOG_CRITICAL(...)	{ ::dat::logger::MainLogger->critical(__VA_ARGS__); DAT_BREAKPOINT(); }
	#define DAT_LOG_ERROR(...)		  ::dat::logger::MainLogger->error(__VA_ARGS__)
	#define DAT_LOG_WARN(...)		{ }
	#define DAT_LOG_DEBUG(...)		{ }
	#define DAT_LOG_TRACE(...)		{ }
	#define DAT_LOG_INFO(...)		{ }
#endif