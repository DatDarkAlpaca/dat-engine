#pragma once
#include "../IEvent.h"

namespace dat
{
	class MouseMoveEvent : public IEvent
	{
	public:
		MouseMoveEvent(double xPos, double yPos) 
			: IEvent(EventType::MOUSE_MOVE_EVENT), x(xPos), y(yPos)
		{

		}

		STATIC_EVENT_TYPE(MOUSE_MOVE_EVENT)

	public:
		double x, y;
	};
}