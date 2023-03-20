#pragma once
#include "../IEvent.h"
#include "KeyButtonEvent.h"

namespace dat
{
	class KeyRepeatEvent : public KeyButtonEvent
	{
	public:
		KeyRepeatEvent(Key key, Mods mods)
			: KeyButtonEvent(key, InputAction::INPUT_REPEAT, mods, EventType::KEY_REPEAT_EVENT)
		{

		}

		STATIC_EVENT_TYPE(KEY_REPEAT_EVENT)
	};
}