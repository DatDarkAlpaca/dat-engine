#pragma once
#include "Core/Logger/Logger.hpp"

namespace dat
{
	inline void __dat_assert(const char* condition, const char* message, const char* file, uint64_t line)
	{
 		DAT_LOG_CRITICAL("[Assert]: '{}' failed. [{}]\nFile: {} [{}]", condition, message, file, line);
	}

#define DAT_ASSERT(condition, message)										\
	{																		\
		if(condition) { }													\
		else																\
		{																	\
			dat::__dat_assert(#condition, message, __FILE__, __LINE__);		\
		}																	\
	}

#define DAT_ASS(condition)																	\
	{																						\
		if(condition) { }																	\
		else																				\
		{																					\
			dat::__dat_assert(#condition, "No message provided", __FILE__, __LINE__);		\
		}																					\
	}
}