#pragma once
#include "../IEvent.h"
#include "MouseButtonEvent.h"

namespace dat
{
	class KeyReleasedEvent : public KeyButtonEvent
	{
	public:
		KeyReleasedEvent(int key, int mods)
			: KeyButtonEvent(key, KeyAction::KEY_RELEASE, mods, EventType::KEY_RELEASED_EVENT)
		{

		}

		STATIC_EVENT_TYPE(KEY_RELEASED_EVENT)
	};
}