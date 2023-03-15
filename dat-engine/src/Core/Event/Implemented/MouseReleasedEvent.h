#pragma once
#include "../IEvent.h"
#include "KeyButtonEvent.h"

namespace dat
{
	class MouseReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseReleasedEvent(int button, int mods)
			: MouseButtonEvent(button, MouseAction::BTN_RELEASE, mods, EventType::MOUSE_RELEASED_EVENT)
		{

		}

		STATIC_EVENT_TYPE(MOUSE_RELEASED_EVENT)
	};
}