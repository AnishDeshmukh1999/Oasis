#include"../oepch.h"
#pragma once
#include"Core.h"
#include"Window.h"
#include"LayerStack.h"
#include"Layer.h"
#include"Events/ApplicationEvent.h"
#include"loguru.hpp"

namespace Oasis {
	class  OE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void onEvent(Event& e);
		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);
		static void setRunning(bool run);
	private:
		bool onWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_window;
		bool m_running = true;
		LayerStack m_layerStack;
	};
	Application* CreateApplication();
}

