#pragma once
#include "Event/IEvent.h"
#include "API.h"

namespace dat
{
	class DatApplication;

	class DAT_API ILayer
	{
	public:
		ILayer(DatApplication* application) : application(application) { }

		virtual ~ILayer() = default;

	public:
		virtual void onLayerAdded() { }

		virtual void onLayerRemoved() { }

		virtual void onUpdate() { }

		virtual void onRender() { }

		virtual void onEvent(IEvent& event) { }

	protected:
		DatApplication* application;
	};
}