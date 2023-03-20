#pragma once
#include "../IEvent.h"
#include "KeyButtonEvent.h"

namespace dat
{
	class MouseReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseReleasedEvent(MouseButton button, Mods mods)
			: MouseButtonEvent(button, InputAction::INPUT_RELEASE, mods, EventType::MOUSE_RELEASED_EVENT)
		{

		}

		STATIC_EVENT_TYPE(MOUSE_RELEASED_EVENT)
	};
}