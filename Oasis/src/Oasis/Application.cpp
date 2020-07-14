#include "Application.h"
#include"Events/ApplicationEvent.h"
#include"Log.h"
namespace Oasis {
	Application::Application()
	{
	}

	Application::~Application()
	{
	}
	void Application::Run() {
		WindowResizeEvent w(1920, 1080);
		OE_TRACE(w);
		while (true);
	}

}