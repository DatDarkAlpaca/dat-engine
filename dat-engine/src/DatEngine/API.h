#pragma once
#include <numeric>

// Debug:
#if defined(_DEBUG)
	#if !defined(DAT_DEBUG)
		#define DAT_DEBUG
	#endif
#endif

// DLL Exports & Imports
#ifdef DAT_EXPORT

	#ifdef _MSC_VER
		#define DAT_API __declspec(dllexport)
	#else
		#define DAT_API
	#endif

#elif DAT_IMPORT

	#ifdef _MSC_VER
		#define DAT_API  __declspec(dllimport)
	#else
		#define DAT_API 
	#endif

#endif

// Plaftorm Detection:
#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32)
	#define DAT_WINDOWS_PLATFORM
#endif