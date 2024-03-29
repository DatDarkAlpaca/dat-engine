#include "LayerStack.h"
#include "Timestep/Timestep.h"

namespace dat
{
	LayerStack::~LayerStack()
	{
		for (ILayer* layer : m_Layers)
			delete layer;
		m_Layers.clear();
	}

	void LayerStack::addLayer(ILayer* layer)
	{
		m_Layers.push_back(layer);
		layer->onLayerAdded();
	}

	void LayerStack::onUpdate(Timestep dt)
	{
		for (ILayer* layer : m_Layers)
			layer->onUpdate(dt);
	}

	void LayerStack::onRender()
	{
		for (ILayer* layer : m_Layers)
			layer->onRender();
	}

	void LayerStack::onEvent(IEvent& event)
	{
		for (ILayer* layer : m_Layers)
			layer->onEvent(event);
	}
}