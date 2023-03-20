#pragma once
#include "../IEvent.h"
#include "KeyButtonEvent.h"

namespace dat
{
	class KeyPressedEvent : public KeyButtonEvent
	{
	public:
		KeyPressedEvent(Key key, Mods mods)
			: KeyButtonEvent(key, InputAction::INPUT_PRESS, mods, EventType::KEY_PRESSED_EVENT)
		{

		}

		STATIC_EVENT_TYPE(KEY_PRESSED_EVENT)
	};
}