#pragma once
#include "pch.h"
#include "../IEvent.h"

namespace dat
{
	enum KeyAction
	{
		KEY_RELEASE = GLFW_RELEASE,
		KEY_PRESS = GLFW_PRESS,
		KEY_REPEAT = GLFW_REPEAT
	};

	class KeyButtonEvent : public IEvent
	{
	public:
		KeyButtonEvent(int key, KeyAction action, int mods, EventType type = EventType::KEY_BUTTON_EVENT)
			: IEvent(type), key(key), action(action), mods(mods)
		{

		}

		STATIC_EVENT_TYPE(KEY_BUTTON_EVENT)

	public:
		KeyAction action;
		int key, mods;
	};

#ifdef DAT_DEBUG
	// TODO: Add debug functions.
#endif
}