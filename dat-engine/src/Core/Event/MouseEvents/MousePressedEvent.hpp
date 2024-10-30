#pragma once
#include "MouseEvent.hpp"

namespace dat
{
	struct MousePressedEvent : public Event
	{
		DEFINE_EVENT(EventType::MOUSE_PRESSED);

	public:
		MousePressedEvent(MouseButton button)
			: button(button)
		{

		}

	public:
		MouseButton button;
	};
}