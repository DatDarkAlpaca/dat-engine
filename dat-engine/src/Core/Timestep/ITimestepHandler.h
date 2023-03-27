#pragma once
#include "Timestep.h"

namespace dat
{
	class ITimestepHandler
	{
	public:
		ITimestepHandler() = default;

	public:
		const Timestep& restart()
		{
			double currentTime = getTimeSeconds();
			double deltaTime = currentTime - m_LastTime;
			m_LastTime = currentTime;

			return { deltaTime };
		}

	private:
		virtual double getTimeSeconds() const = 0;

	protected:
		double m_LastTime = 0;
	};

	dat_unique<ITimestepHandler> getTimestepHandler();
}