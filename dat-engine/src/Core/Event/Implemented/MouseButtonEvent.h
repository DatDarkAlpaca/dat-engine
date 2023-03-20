#pragma once
#include "pch.h"
#include "../IEvent.h"
#include "Input/InputAction.h"
#include "Input/MouseButton.h"

namespace dat
{
	class MouseButtonEvent : public IEvent
	{
	public:
		MouseButtonEvent(MouseButton button, InputAction action, Mods mods, EventType type = EventType::MOUSE_BUTTON_EVENT)
			: IEvent(type), button(button), action(action), mods(mods)
		{
		
		}

		STATIC_EVENT_TYPE(MOUSE_BUTTON_EVENT)

	public:
		InputAction action;
		MouseButton button;
		Mods mods;
	};
}