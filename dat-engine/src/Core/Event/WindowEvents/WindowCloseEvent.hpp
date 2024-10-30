#pragma once
#include "Core/Event/Event.hpp"

namespace dat
{
	class WindowCloseEvent : public Event
	{
		DEFINE_EVENT(EventType::WINDOW_CLOSE);
	};
}