#include"../oepch.h"
#include "Application.h"
#include"Events/ApplicationEvent.h"
#include"Events/ApplicationEvent.h"
#include <glad\glad.h>	
namespace Oasis {
#define EVENT_BIND_FN(x) std::bind(&x,this,std::placeholders::_1)
	Application::Application()
	{
		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->setEventCallbackFn(EVENT_BIND_FN(Application::onEvent));
	}

	Application::~Application()
	{
	}
	void Application::Run() {
		while (m_running) {
			for (Layer* layer : m_layerStack) {
				layer->onUpdate();
			}
			m_window->onUpdate();
		}
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(EVENT_BIND_FN(Application::onWindowClose));
		LOG_F(INFO,"%s",e.toString().c_str());
		for (auto it = m_layerStack.end(); it != m_layerStack.begin();) {
			(*--it)->onEvent(e);
			if (e.isHandled()) {
				break;
				}
		}
	}

	void Application::pushLayer(Layer* layer)
	{
		m_layerStack.pushLayer(layer);
	}

	void Application::pushOverlay(Layer* layer)
	{
		m_layerStack.pushOverlay(layer);
	}


	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		m_running = false;
		return true;
	}

	

}