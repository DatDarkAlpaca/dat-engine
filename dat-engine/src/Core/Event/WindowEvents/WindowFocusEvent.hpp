#pragma once
#include "Core/Event/Event.hpp"

namespace dat
{
	class WindowFocusEvent : public Event
	{
		DEFINE_EVENT(EventType::WINDOW_FOCUS_CHANGED);

	public:
		WindowFocusEvent(int focusState)
			: focusState(focusState)
		{

		}

	public:
		int focusState;
	};
}