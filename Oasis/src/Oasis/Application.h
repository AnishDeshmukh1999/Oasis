#pragma once
#include"Core.h"
#include"Window.h"
namespace Oasis {
	class  OE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	private:
		std::unique_ptr<Window> m_window;
		bool m_running = true;
	};
	Application* CreateApplication();
}

