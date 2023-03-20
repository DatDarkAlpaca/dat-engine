#pragma once
#include "../IEvent.h"
#include "MouseButtonEvent.h"

namespace dat
{
	class KeyReleasedEvent : public KeyButtonEvent
	{
	public:
		KeyReleasedEvent(Key key, Mods mods)
			: KeyButtonEvent(key, InputAction::INPUT_RELEASE, mods, EventType::KEY_RELEASED_EVENT)
		{

		}

		STATIC_EVENT_TYPE(KEY_RELEASED_EVENT)
	};
}