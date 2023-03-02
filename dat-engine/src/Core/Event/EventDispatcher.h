#pragma once
#include <functional>
#include "IEvent.h"

namespace dat::core
{
	class EventDispatcher
	{
	public:
		EventDispatcher(IEvent& event)
			: m_Event(event)
		{

		}

	template<typename TargetEvent>
	bool dispatch(const std::function<bool(TargetEvent&)>& function)
	{
		if (TargetEvent::eventType() == m_Event.m_EventType)
		{
			function(static_cast<TargetEvent&>(m_Event));
			return true;
		}

		return false;
	}

	private:
		IEvent& m_Event;
	};
}