#pragma once
#include "pch.h"
#include "API.h"
#include "ILayer.h"

namespace dat
{
	class DAT_API LayerStack
	{
	public:
		LayerStack() = default;

		~LayerStack()
		{
			for (ILayer* layer : m_Layers)
				delete layer;
			m_Layers.clear();
		}

	public:
		void addLayer(ILayer* layer)
		{
			m_Layers.push_back(layer);
			layer->onLayerAdded();
		}

	public:
		void onUpdate() 
		{
			for (ILayer* layer : m_Layers)
				layer->onUpdate();
		}

		void onRender()
		{
			for (ILayer* layer : m_Layers)
				layer->onRender();
		}

		void onEvent(IEvent& event) 
		{ 
			for (ILayer* layer : m_Layers)
				layer->onEvent(event);
		}

	public:
		std::vector<ILayer*> m_Layers;
	};
}