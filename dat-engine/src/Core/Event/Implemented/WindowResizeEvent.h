#pragma once
#include "../IEvent.h"

namespace dat
{
	class WindowResizeEvent : public IEvent
	{
	public:
		WindowResizeEvent(int width, int height) 
			: IEvent(EventType::WINDOW_RESIZE_EVENT), width(width), height(height)
		{

		}

		STATIC_EVENT_TYPE(WINDOW_RESIZE_EVENT)

	public:
		int width = -1, height = -1;
	};
}