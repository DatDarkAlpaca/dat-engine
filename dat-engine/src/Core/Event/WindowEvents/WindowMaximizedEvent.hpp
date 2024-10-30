#pragma once
#include "Core/Event/Event.hpp"

namespace dat
{
	class WindowMaximizedEvent : public Event
	{
		DEFINE_EVENT(EventType::WINDOW_MAXIMIZED);

	public:
		WindowMaximizedEvent(int maximizationState)
			: maximizationState(maximizationState)
		{

		}

	public:
		int maximizationState;
	};
}