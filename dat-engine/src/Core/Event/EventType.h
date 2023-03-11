#pragma once

namespace dat
{
	enum class EventType
	{
		NONE_EVENT = 0,
		WINDOW_CLOSE_EVENT,
		WINDOW_RESIZE_EVENT,

		MOUSE_MOVE_EVENT,

		AMOUNT_EVENT
	};
}