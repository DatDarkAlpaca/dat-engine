#pragma once
#include "pch.h"
#include "../IEvent.h"

#include "Input/InputAction.h"
#include "Input/Key.h"
#include "Input/Mods.h"

namespace dat
{
	class KeyButtonEvent : public IEvent
	{
	public:
		KeyButtonEvent(Key key, InputAction action, Mods mods, EventType type = EventType::KEY_BUTTON_EVENT)
			: IEvent(type), key(key), action(action), mods(mods)
		{

		}

		STATIC_EVENT_TYPE(KEY_BUTTON_EVENT)

	public:
		InputAction action;
		Key key;
		Mods mods;
	};
}