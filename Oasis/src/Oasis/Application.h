#pragma once
#include"Core.h"
namespace Oasis {
	class  OE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};
	Application* CreateApplication();
}

