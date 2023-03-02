#pragma once
#include "Event/IEvent.h"

namespace dat::core
{
	class ILayer
	{
	public:
		virtual ~ILayer() = default;

	public:
		virtual void onLayerAdded() { }

		virtual void onLayerRemoved() { }

		virtual void onUpdate() { }

		virtual void onEvent(IEvent& event) { }
	};
}