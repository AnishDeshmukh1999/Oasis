#include "Application.h"
#include"Events/ApplicationEvent.h"
#include"Log.h"
namespace Oasis {
	Application::Application()
	{
		m_window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}
	void Application::Run() {
		WindowCloseEvent w;
		OE_FATAL(w);
		OE_FATAL("Welcome var={0}", 5);
		while (m_running) {
			int q = 10;
			m_window->onUpdate();
		}
	}

}