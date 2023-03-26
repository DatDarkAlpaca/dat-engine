#include "ITimestepHandler.h"
#include "Platform/Windows/TimestepWindows.h"
#include "Platform/TimestepGeneral.h"

namespace dat
{
	ITimestepHandler* getTimestepHandler()
	{
#ifndef DAT_WINDOWS_PLATFORM
		return new TimestepWindows();
#else
		return new TimestepGeneral();
#endif
	}
}