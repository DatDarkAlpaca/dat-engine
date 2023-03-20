#pragma once
#include "../IEvent.h"
#include "MouseButtonEvent.h"

namespace dat
{
	class MousePressedEvent : public MouseButtonEvent
	{
	public:
		MousePressedEvent(MouseButton button, Mods mods)
			: MouseButtonEvent(button, InputAction::INPUT_PRESS, mods, EventType::MOUSE_PRESSED_EVENT)
		{

		}

		STATIC_EVENT_TYPE(MOUSE_PRESSED_EVENT)
	};
}