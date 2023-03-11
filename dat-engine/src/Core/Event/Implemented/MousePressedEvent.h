#pragma once
#include "../IEvent.h"
#include "MouseButtonEvent.h"

namespace dat
{
	class MousePressedEvent : public MouseButtonEvent
	{
	public:
		MousePressedEvent(int button, int mods)
			: MouseButtonEvent(button, MouseAction::BTN_PRESS, mods, EventType::MOUSE_PRESSED_EVENT)
		{

		}

		STATIC_EVENT_TYPE(MOUSE_PRESSED_EVENT)
	};
}