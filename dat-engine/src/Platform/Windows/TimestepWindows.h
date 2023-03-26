#include "pch.h"
#include "WindowsHeader.h"
#include "Timestep/ITimestepHandler.h"

namespace dat
{
	class TimestepWindows final : public ITimestepHandler
	{
	public:
		TimestepWindows()
		{
			LARGE_INTEGER perfData;

			if (!QueryPerformanceFrequency(&perfData))
			{
				DAT_CORE_ERROR("The QueryPerformanceFrequency operation failed.");
				return;
			}

			m_Frequency = double(perfData.QuadPart);
			QueryPerformanceCounter(&perfData);

			m_CounterStart = perfData.QuadPart;
		}

	public:
		double getTimeSeconds() const override
		{
			LARGE_INTEGER perfData;
			QueryPerformanceCounter(&perfData);

			return double(perfData.QuadPart - m_CounterStart) / m_Frequency;
		}

	public:
		double m_Frequency = 0;
		std::int64_t m_CounterStart = 0;
	};
}