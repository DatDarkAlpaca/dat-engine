#pragma once
#include "../IEvent.h"
#include "MouseButtonEvent.h"

namespace dat
{
	class MouseScrollEvent : public IEvent
	{
	public:
		MouseScrollEvent(double xOffset, double yOffset)
			: IEvent(EventType::MOUSE_SCROLL_EVENT), xOffset(xOffset), yOffset(yOffset)
		{

		}

		STATIC_EVENT_TYPE(MOUSE_SCROLL_EVENT)

	public:
		double xOffset, yOffset;
	};
}