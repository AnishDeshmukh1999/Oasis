#include "LayerStack.h"
namespace Oasis {
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_layers)
			delete layer;
	}
	void LayerStack::pushLayer(Layer* layer)
	{
		m_layers.emplace(m_layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}
	void LayerStack::popLayer(Layer* layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.begin()+ m_LayerInsertIndex, layer);
		if (it != m_layers.end()) {
			m_layers.erase(it);
			m_LayerInsertIndex--;
		}
	}
	void LayerStack::pushOverlay(Layer* overlay)
	{
		m_layers.emplace_back(overlay);
	}
	void LayerStack::popOverlay(Layer* overlay)
	{
		auto it = std::find(m_layers.begin()+m_LayerInsertIndex, m_layers.end(), overlay);
		if (it != m_layers.end()) {
			m_layers.erase(it);
		}
	}
}