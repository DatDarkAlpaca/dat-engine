#pragma once
#include "../IEvent.h"
#include "KeyButtonEvent.h"

namespace dat
{
	class KeyPressedEvent : public KeyButtonEvent
	{
	public:
		KeyPressedEvent(int key, int mods)
			: KeyButtonEvent(key, KeyAction::KEY_PRESS, mods, EventType::KEY_PRESSED_EVENT)
		{

		}

		STATIC_EVENT_TYPE(KEY_PRESSED_EVENT)
	};
}