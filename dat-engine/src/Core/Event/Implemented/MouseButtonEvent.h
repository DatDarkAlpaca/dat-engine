#pragma once
#include "pch.h"
#include "../IEvent.h"

namespace dat
{
	enum MouseAction
	{
		BTN_RELEASE = GLFW_RELEASE,
		BTN_PRESS	= GLFW_PRESS,
		BTN_REPEAT  = GLFW_REPEAT
	};

	class MouseButtonEvent : public IEvent
	{
	public:
		MouseButtonEvent(int button, MouseAction action, int mods, EventType type = EventType::MOUSE_BUTTON_EVENT)
			: IEvent(type), button(button), action(action), mods(mods)
		{
		
		}

		STATIC_EVENT_TYPE(MOUSE_BUTTON_EVENT)

	public:
		MouseAction action;
		int button, mods;
	};

#ifdef DAT_DEBUG

	inline std::string debugButtonName(int button)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
			return "BTN_LEFT";

		else if (button == GLFW_MOUSE_BUTTON_LEFT)
			return "BTN_RIGHT";

		else
			return "BTN_" + std::to_string(button + 1);
	}

	inline std::string debugButtonMods(int mods)
	{
		std::vector<std::string> modResults;

		if (mods & GLFW_MOD_SHIFT)
			modResults.push_back("SHIFT");

		if (mods & GLFW_MOD_CONTROL)
			modResults.push_back("CTRL");

		if (mods & GLFW_MOD_ALT)
			modResults.push_back("ALT");

		if (mods & GLFW_MOD_SUPER)
			modResults.push_back("SUPER");

		if (mods & GLFW_MOD_CAPS_LOCK)
			modResults.push_back("CAPS");

		if (mods & GLFW_MOD_NUM_LOCK)
			modResults.push_back("NUM_LOCK");

		if (modResults.size() == 0)
			return "NONE";

		if (modResults.size() == 1)
			return modResults.back();

		std::string str = "";
		for (size_t i = 0; i != modResults.size(); ++i)
		{
			if(i == modResults.size() - 1)
				str += modResults[i];
			else
				str += modResults[i] + " | ";
		}

		return str;
	}

#endif
}