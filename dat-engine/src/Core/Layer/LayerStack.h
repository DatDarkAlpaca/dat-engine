#pragma once
#include "pch.h"
#include "API.h"
#include "ILayer.h"

namespace dat
{
	class DAT_API LayerStack
	{
	public:
		~LayerStack();

	public:
		void addLayer(ILayer* layer);

	public:
		void onUpdate(Timestep dt);

		void onRender();

		void onEvent(IEvent& event);

	public:
		std::vector<ILayer*> m_Layers;
	};
}