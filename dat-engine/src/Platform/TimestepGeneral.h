#include "pch.h"
#include "Timestep/ITimestepHandler.h"

namespace dat
{
	class TimestepGeneral final : public ITimestepHandler
	{
	public:
		double getTimeSeconds() const override
		{
			using namespace std::chrono;
			return duration_cast<duration<double>>(high_resolution_clock::now().time_since_epoch()).count();
		}
	};
}