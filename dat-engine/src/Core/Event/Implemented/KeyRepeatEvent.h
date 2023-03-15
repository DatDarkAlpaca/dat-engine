#pragma once
#include "../IEvent.h"
#include "KeyButtonEvent.h"

namespace dat
{
	class KeyRepeatEvent : public KeyButtonEvent
	{
	public:
		KeyRepeatEvent(int key, int mods)
			: KeyButtonEvent(key, KeyAction::KEY_REPEAT, mods, EventType::KEY_REPEAT_EVENT)
		{

		}

		STATIC_EVENT_TYPE(KEY_REPEAT_EVENT)
	};
}