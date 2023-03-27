#include "ITimestepHandler.h"
#include "Platform/Windows/TimestepWindows.h"
#include "Platform/TimestepGeneral.h"

namespace dat
{
	ITimestepHandler* getTimestepHandler()
	{
#ifdef DAT_PLATFORM_WINDOWS
		return new TimestepWindows();
#else
		return new TimestepGeneral();
#endif
	}
}