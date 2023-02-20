#pragma once

namespace dat::core
{
	struct ApplicationStatus
	{
		bool isGLFWInitialized = false;
		bool isGLEWInitialized = false;
	};

	inline ApplicationStatus applicationStatus;
}