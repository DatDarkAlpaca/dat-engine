#include "ITimestepHandler.h"
#include "Platform/Windows/TimestepWindows.h"
#include "Platform/TimestepGeneral.h"

namespace dat
{
	dat_unique<ITimestepHandler> getTimestepHandler()
	{
#ifdef DAT_PLATFORM_WINDOWS
		return std::make_unique<TimestepWindows>();
#else
		return std::make_unique<TimestepGeneral>();
#endif
	}
}