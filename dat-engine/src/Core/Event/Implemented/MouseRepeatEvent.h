#pragma once
#include "../IEvent.h"
#include "MouseButtonEvent.h"

namespace dat
{
	class MouseRepeatEvent : public MouseButtonEvent
	{
	public:
		MouseRepeatEvent(MouseButton button, Mods mods)
			: MouseButtonEvent(button, InputAction::INPUT_REPEAT, mods, EventType::MOUSE_REPEAT_EVENT)
		{

		}

		STATIC_EVENT_TYPE(MOUSE_REPEAT_EVENT)
	};
}