#pragma once
#include "../IEvent.h"

namespace dat::core
{
	class WindowCloseEvent : public IEvent
	{
	public:
		WindowCloseEvent() : IEvent(EventType::WINDOW_CLOSE_EVENT) { }

		STATIC_EVENT_TYPE(WINDOW_CLOSE_EVENT)
	};
}