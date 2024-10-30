#pragma once

#if !defined(DAT_PROJECT_NAME)
	#define DAT_PROJECT_NAME "DatEngine"
#endif

#if defined(_DEBUG) && !defined(DAT_DEBUG)
	#define DAT_DEBUG
#elif defined(NDEBUG) && !defined(DAT_RELEASE)
	#define DAT_RELEASE
#endif

#ifdef DAT_PLATFORM_WINDOWS
	#define DAT_BREAKPOINT() __debugbreak()
#elif defined(__linux__)
	#define DAT_PLATFORM_LINUX
	#define DAT_BREAKPOINT() __builtin_trap()
#elif defined(__APPLE__)
	#define DAT_PLATFORM_APPLE
	#define DAT_BREAKPOINT() __builtin_trap()
#elif defined(__ANDROID__)
	#define DAT_PLATFORM_ANDROID
	#define DAT_BREAKPOINT() __builtin_trap()
#else
	#error Unsupported platform
#endif