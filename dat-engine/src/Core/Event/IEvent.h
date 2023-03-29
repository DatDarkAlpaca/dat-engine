#pragma once
#include "API.h"
#include "EventType.h"

#define STATIC_EVENT_TYPE(type) static EventType eventType() { return EventType::type; }

namespace dat
{
	class DAT_API IEvent
	{
		friend class EventDispatcher;

	public:
		virtual ~IEvent() = default;

	protected:
		IEvent(EventType eventType) : m_EventType(eventType) { }

	private:
		EventType m_EventType = EventType::NONE_EVENT;
		bool m_Handled = false;
	};
}