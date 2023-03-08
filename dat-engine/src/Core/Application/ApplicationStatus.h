#pragma once

namespace dat
{
	struct ApplicationStatus
	{
		bool isGLFWInitialized = false;
		bool isGLEWInitialized = false;
	};

	inline ApplicationStatus applicationStatus;
}